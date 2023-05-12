import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch


def create_keymap(keys, figsize=(10, 5), upscale=10):
    """Generate an image of a keyboard layout using matplotlib.

    The keyboard layout is defined by `keys`, which is a NumPy array. Each
    inner list represents a row of keys, where the values are the widths of
    the keys in units. The function returns the matplotlib figure.
    """

    # Create figure and axes objects
    fig, ax = plt.subplots(figsize=figsize)

    # Set aspect ratio
    ax.set_aspect("equal")

    # Remove frame
    ax.axis("off")

    # Iterate over each row of keys
    for i, row in enumerate(keys):
        # Set y coordinate of this row
        y = (len(keys) - 1 - i) * upscale

        # Set x coordinate of first key in row
        x = row[0] * upscale

        # Iterate over each key in row, except the first one
        for key_width in row[1:]:
            # Next row at zero-width key
            if not key_width: break

            # Create rectangle object for this key
            rect_style = "round,pad={},rounding_size={}"\
                         .format(-0.05*upscale, 0.15*upscale)
            rect = FancyBboxPatch((x, y), key_width * upscale, upscale,
                                  facecolor="grey", boxstyle=rect_style,
                                  ec="none")

            # Add rectangle to axes object
            ax.add_patch(rect)

            # Increment x coordinate for next key
            x += key_width * upscale

    # Set x and y limits
    ax.set_xlim([0, sum(keys[0])*upscale])
    ax.set_ylim([0, len(keys)*upscale])

    # Remove ticks and tick labels
    ax.set_xticks([])
    ax.set_yticks([])

    # Return the axes
    return fig, ax
