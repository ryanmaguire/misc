################################################################################
#                                   LICENSE                                    #
################################################################################
#   This file is free software: you can redistribute it and/or modify          #
#   it under the terms of the GNU General Public License as published by       #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   This file is distributed in the hope that it will be useful,               #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with this file.  If not, see <https://www.gnu.org/licenses/>.        #
################################################################################
#   Purpose:                                                                   #
#       Draws a contour plot of z = xy in Julia using GLMakie.                 #
#   Notes:                                                                     #
#       1.) Andy Keavey contributed this code for MITx 18.02.1x online course  #
#           during the Fall 2024 semester. Credit: https://github.com/a2k42.   #
#           A few minor edits have been made from the original work.           #
#       2.) When run at the command line, the PNG is created and saved. In     #
#           interactive mode you may use a slider to vary the constant z plane.#
################################################################################
#   Author:     Andy Keavey                                                    #
#   Date:       2024/08/10                                                     #
################################################################################
using GLMakie

GLMakie.activate!(; float = true)
set_theme!(theme_black())

# The function we are plotting: z = x * y.
function surface_parametrization(x_val, y_val)
    return x_val * y_val
end

# Array for sampling over the x and y axes.
x = [value for value in range(-3, 3, 100)]
y = [value for value in range(-3, 3, 100)]

# Values for the level sets of the function.
z_levels = [value for value in -5:5]

# Parameters for the rendering.
figure_label = "Multivariable Calculus: Plotting Surfaces"
z_obs = Observable(0.2)
alpha_gray = (:gray, 0.3)
fontsize = Observable(12)
fontsize[] = 36

# Two figures, side-by-side, one for the contours and one for the surface plot.
fig = Figure(size = (1200, 600))
ax1 = Axis(fig[1, 1], title = "Level Curve")
ax2 = Axis3(fig[1, 2], title = "Surface Plot")

# Make both plots and create a header for the entire figure.
contour!(ax1, x, y, surface_parametrization, labels = true, levels = z_levels)
surface!(ax2, x, y, surface_parametrization)
Label(fig[0, :], figure_label, fontsize = fontsize)

# Begin interactive portion.
# This creates a slider that varies the constant z plane.
zs = lift(z_obs) do z
    fill(z, size(x)[1], size(y)[1])
end

surface!(ax2, x, y, zs, color = [alpha_gray for i in 1:2, j in 1:2])
slider1 = Slider(fig[2, :], range = -2:0.1:7, startvalue = 0.2)

on(slider1.value) do height
    z_obs[] = height
end
# End interactive portion.

# Save the plot for future viewing. In command-line mode, the final PNG is
# the only thing the user will be able to see.
save("contour_plot_of_z_equals_xy.png", fig)
