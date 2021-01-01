# Cheat and add module to path
import sys
sys.path.insert(0, "/workspaces/dubins/build/scripts/dubins_python/")

# Imports
import dubins_python

import math
import matplotlib.pyplot as plt

# Function to add a path plot to an axis
def plot_path(path, axs, color):
    x = []
    y = []
    u = []
    v = []

    for state in path:
        x.append(state.position.x)
        y.append(state.position.y)
        u.append(math.cos(state.heading))
        v.append(math.sin(state.heading))

    axs.plot(x,y, linewidth=1.5, color=color)
    axs.quiver(x,y,u,v, scale=5.0, scale_units='xy')

# Create dubins path
start = dubins_python.State(dubins_python.Vector2D(0.0, 0.0), math.pi/2)
end = dubins_python.State(dubins_python.Vector2D(1.5, 1.5), -math.pi/2)

options = dubins_python.Options()
options.turning_radius  = 2.0
options.max_segment_length = 0.1
options.min_number_of_segments = 20

obj = dubins_python.Dubins(start, end, options)
path = obj.segmented_path(options)

# Plot result
fig, axs = plt.subplots(1, 1)
fig.set_size_inches(8.25, 5.25)

a0 = obj.segmented_rsr(options)
a1 = obj.segmented_lsl(options)
a2 = obj.segmented_rsl(options)
a3 = obj.segmented_lsr(options)
a4 = obj.segmented_rlr(options)
a5 = obj.segmented_lrl(options)

print(len(a0))
print(len(a1))
print(len(a2))
print(len(a3))
print(len(a4))
print(len(a5))

plot_path(path, axs, 'b')
plot_path(a0, axs, 'b')
plot_path(a1, axs, 'r')
plot_path(a2, axs, 'g')
plot_path(a3, axs, 'y')
plot_path(a4, axs, 'c')
plot_path(a5, axs, 'm')

axs.set_xlabel('X')
axs.set_ylabel('Y')
axs.grid(True)
axs.axis('equal')
axs.set_title('Dubins path', fontsize=12)

fig.tight_layout()
plt.savefig('test.png')