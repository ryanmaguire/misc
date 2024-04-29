#!/bin/bash
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
#       Below is the beta version of the rssconfig shell script                #
#       that was used to setup Anaconda3 on the user's computer,               #
#       install a few python modules/packages, and then run updates.           #
#       This was used to ensure all of the dependencies for the                #
#       rss_ringoccs package were installed. This was previously tested on     #
#       an iMac and on a macbook pro, both running MacOSX 10.13.4              #
#       High Sierra, as well as Ubuntu 16. The script worked for both          #
#       Linux and Mac operating system's without the user needing to specify   #
#       anything. The present version of rss_ringoccs no longer requires       #
#       nearly as many dependencies and this script is no longer used.         #
################################################################################
if [ ! "$BASH_VERSION" ] ; then
        echo "Please use BASH to run this script ($0)" 1>&2
        exit 1
fi

osstring=`uname`

if [ osstring = "Darwin" ]; then
        fil="Anaconda3-5.1.0-MacOSX-x86_64.sh"
elif [ osstring = "Linux" ];
        fil="Anaconda3-5.1.0-Linux-x86_64.sh"
else
        echo "Operating System not recognized"
        echo "Only MacOSX and Linux supported"
        echo "Exiting script"
        exit 1
fi

web="https://repo.continuum.io/archive/"
webfil="$web$fil"

if [ ! -e "~/anaconda3" ]; then
        echo "Anaconda3 does not currently exist on your computer."
        echo "Running setup scripts now..."

        # Go to your home directory
        cd ~

        # Use cURL to download Anaconda 5.1.0.
        curl -Ok "$webfil"

        # Run the Anaconda installer.
        bash "filename" -b -p ~/anaconda3

        # Remove the shell script from your home directory.
        rm Anaconda3-5.1.0-MacOSX-x86_64.sh

        # Add Anaconda to your path.
        echo 'export PATH="~/anaconda3/bin:$PATH"' >> ~/.bash_profile

        # Update bash_profile.
        source .bash_profile
else
        echo "You already have Anaconda on your computer."
        echo "Running updates..."
fi

# Update conda and install Spiceypy
conda update conda
conda install -c https://conda.anaconda.org/andrewannex spiceypy
