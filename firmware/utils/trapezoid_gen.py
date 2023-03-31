################################################################################
#
# File Description:
#   This python script is just a scratchpad for figuring out/visualizing the
#   trapezoid generators.
#
################################################################################

import numpy as np
from matplotlib import pyplot as plt

DOMAIN = 2**16 - 1

NUM_TRAPS = 4

NUM_SEGMENTS = ((NUM_TRAPS * 2) - 1)

TRAP_WIDTH = DOMAIN // NUM_SEGMENTS

TRAP_CENTERS = [(TRAP_WIDTH // 2) + ((TRAP_WIDTH * 2) * i) for i in range(NUM_TRAPS)]

TRAP_SLOPE = NUM_SEGMENTS

def trap(input_val, center):
    plat_start = center - TRAP_WIDTH//2
    plat_end   = center + TRAP_WIDTH//2

    output = 0

    if (input_val < plat_start):
        output = TRAP_SLOPE * (input_val - plat_start) + DOMAIN
    elif (plat_start <= input_val < plat_end):
        output = DOMAIN
    else: # its is after the plateau end
        output = TRAP_SLOPE * (plat_end - input_val) + DOMAIN

    if (DOMAIN < output):
        output = DOMAIN
    
    if (output < 0):
        output = 0

    return output

traps = [np.linspace(0, DOMAIN, DOMAIN).astype(int) for i in range(NUM_TRAPS)]

for i in range(NUM_TRAPS):
    for n in range(len(traps[i])):
        traps[i][n] = trap(n, TRAP_CENTERS[i])

fig = plt.figure()
ax = fig.add_subplot()

for t in traps:
    ax.plot(t)

plt.show()
