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
#       Poorly written script I used to clean up a git repo.                   #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2023/10/14                                                     #
################################################################################
git filter-repo --path-glob '*.jar' --invert-paths --force
git filter-repo --path-glob '*.so' --invert-paths --force
git filter-repo --path-glob '*.pyc' --invert-paths --force
git filter-repo --path-glob '*.pdf' --invert-paths --force
git filter-repo --path-glob '*.png' --invert-paths --force
git filter-repo --path-glob '*.TAB' --invert-paths --force
git filter-repo --path-glob '*.P' --invert-paths --force
git filter-repo --path-glob '*.p' --invert-paths --force
git filter-repo --path-glob '*.DS_Store' --invert-paths --force
git filter-repo --path-glob '*test' --invert-paths --force
git filter-repo --path-glob 'docs/_build/*' --invert-paths --force
git filter-repo --path-glob 'examples/math_examples/*' --invert-paths --force
git filter-repo --path-glob 'examples/numerical_examples/*' --invert-paths --force
