"""Aggregate keycounts over time and visualize heatmap.

The function makes a query to the local database to read all the past
keycounts. It sums them up and uses matplotlib to generate a visual
representation. The image is returned in SVG format.
"""


import re
import mysql.connector
import sys
import json
import numpy as np
import matplotlib.pyplot as plt
from scipy.ndimage import gaussian_filter


# Define a regular expression to match the variable definitions
var_pattern = re.compile(r"\$(\w+)\s*=\s*[\'\"](.+?)[\'\"]\s*;")

# Open the db_credentials.php file and read its contents
with open("db_credentials.php", "r") as f:
    contents = f.read()

# Find all variable definitions and store them in a dictionary
db_credentials = {}
for match in var_pattern.finditer(contents):
    db_credentials[match.group(1)] = match.group(2)

# Get the user hash argument from the command line
user_hash = sys.argv[1]

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

# Upsample the keycount array
counts_upsampled = np.zeros((counts_total.shape[0] * 10, counts_total.shape[1] * 10))
for i in range(counts_total.shape[0]):
    for j in range(counts_total.shape[1]):
        counts_upsampled[i*10:(i+1)*10, j*10:(j+1)*10] = counts_total[i, j]

# Smooth the array using a Gauss filter
sigma = 4
counts_smoothed = gaussian_filter(counts_upsampled, sigma=sigma)

# Create a new figure and plot the upsampled heatmap
fig = plt.figure()
ax = fig.add_subplot(111)
im = ax.imshow(counts_smoothed, cmap='hot', interpolation='spline16')
fig.colorbar(im)

# Save the plot as heatmap.png
plt.savefig('heatmap.png')

# Exit with return value 0
sys.exit(0)
