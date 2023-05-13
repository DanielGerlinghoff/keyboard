import re
import mysql.connector
import sys
import json
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
from matplotlib.cm import ScalarMappable
from mpl_toolkits.axes_grid1 import make_axes_locatable
from math import ceil
from scipy.ndimage import gaussian_filter

from keymap import create_keymap


def retrieve_keycount(user_hash):
    """Retrieve the key count data for a user from a MySQL database.

    The function reads the credentials for the database from a PHP file named
    db_credentials.php, connects to the database using the provided
    credentials, and executes a SQL query to select the key count data for a
    user with a specified hash. The function returns a NumPy array
    containing the accumulated key count data for the specified user.
    """

    # Define a regular expression to match the variable definitions
    var_pattern = re.compile(r"\$(\w+)\s*=\s*[\'\"](.+?)[\'\"]\s*;")

    # Open the db_credentials.php file and read its contents
    with open("db_credentials.php", "r") as f:
        contents = f.read()

    # Find all variable definitions and store them in a dictionary
    db_credentials = {}
    for match in var_pattern.finditer(contents):
        db_credentials[match.group(1)] = match.group(2)

    # Connect to the MySQL database using the db_credentials dictionary
    cnx = mysql.connector.connect(
        host=db_credentials["servername"],
        user=db_credentials["username"],
        password=db_credentials["password"],
        database=db_credentials["dbname"]
    )

    # Create a cursor to execute SQL queries
    cursor = cnx.cursor()

    # Define the SQL query to select records with a specified user hash
    query = "SELECT time, count FROM keycount WHERE user=%s"

    # Execute the query with the user hash parameter
    cursor.execute(query, (user_hash,))

    # Save keycounts as NumPy array
    counts = []
    for (time, count_str) in cursor:
        count_list = json.loads(count_str)
        counts.append(np.array(count_list))
    counts_total = np.stack(counts).sum(axis=0)

    # Close the cursor and database connection
    cursor.close()
    cnx.close()

    # Return result
    return counts_total


def draw_heatmap(keys, counts):
    """
    Draw a heatmap using a colormap to represent the counts of each key.

    The function creates a keymap basemap. The keycount array is then upscaled
    and shifted to the key positions. The heatmap is smoothed using a Gaussian
    filter. A colorbar is added to the plot along with a label. The plot is
    saved as heatmap.png.
    """

    # Create the keymap basemap
    upscale = 8
    fig, ax = create_keymap(keys, figsize=(10, 3), upscale=upscale)

    # Create a zero np array that matches the size of ax
    heatmap = np.zeros((ceil(ax.get_ylim()[1]), ceil(ax.get_xlim()[1])))

    # Upscale heatmap and shift values to key positions
    keys_center = np.cumsum(keys, axis=1) - (keys / 2.0)
    keys_center = np.ceil(keys_center[:, 1:] * upscale).astype(int)

    for row in range(counts.shape[0]):
        row_idx = np.arange(row * upscale, (row + 1) * upscale)

        for col in range(counts.shape[1]):
            if keys[row, col+1] == 0: continue

            col_idx = np.arange(keys_center[row, col] - upscale // 2,
                                keys_center[row, col] + upscale // 2)

            np.set_printoptions(threshold=np.inf)
            row_grid, col_grid = np.meshgrid(row_idx, col_idx)
            heatmap[row_grid, col_grid] = counts[row, col]

    # Invert the y axis of the array
    heatmap = heatmap[::-1]
    heatmap_max = heatmap.max()

    # Smooth the array using a Gauss filter and normalize it
    sigma = 4
    heatmap_smooth = gaussian_filter(heatmap, sigma=sigma)
    heatmap_smooth = heatmap_smooth / heatmap_smooth.max() * heatmap_max

    # Define the colormap as a dictionary with the colors and alpha values
    colors = [(0, 0, 1, .0), (0, 1, 1, .5), (1, 1, 0, .8), (1, 0, 0, .9)]
    cmap_alpha = mcolors.LinearSegmentedColormap.from_list("heat", colors)

    # Create a new figure and plot the smoothed heatmap
    im = ax.imshow(heatmap_smooth, cmap=cmap_alpha,
                   interpolation="spline16", zorder=2)

    # Add a colorbar with opaque colorbar and a label
    divider = make_axes_locatable(ax)
    cax = divider.append_axes("right", size="3%", pad=0.8)

    cmap_opaque = cmap_alpha.copy()
    cmap_opaque._init()
    cmap_opaque._lut[:, -1] = np.clip(cmap_opaque._lut[:, -1] + 0.2, 0, 1)

    smap = ScalarMappable(norm=mcolors.Normalize(0, heatmap_max),
                          cmap=cmap_opaque)
    cbar = plt.colorbar(smap, cax=cax)
    cbar.ax.tick_params(labelsize=14, labelcolor="black")
    cbar.outline.set_linewidth(0.5)

    plt.rcParams["font.family"] = "Consolas, monospace"
    cbar.ax.text(-0.5, cbar.ax.get_ylim()[1] / 2, "Key Count",
                 fontsize=16, color="black", rotation=90,
                 va="center", ha="right")

    # Save the plot as heatmap.png
    fig.tight_layout()
    plt.savefig("heatmap.png", dpi=100, transparent=True)


if __name__ == "__main__":
    # Get the user hash argument from the command line
    user_hash = sys.argv[1]

    # Retrieve key widths and counts from the database
    keys = np.array([[0.75, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 2.00],
                     [0.25, 1.50, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.50],
                     [0.00, 1.75, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 2.25, 0.00],
                     [0.00, 1.75, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.75, 1.00, 1.00],
                     [0.25, 1.50, 1.25, 1.50, 6.25, 1.25, 1.50, 1.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00]])
    counts = retrieve_keycount(user_hash)

    # Save the heatmap
    draw_heatmap(keys, counts)

    # Exit with return value 0
    sys.exit(0)
