#!/usr/bin/python
"""
==============================================================================

  This file is part of GPSTk, the GPS Toolkit.

  The GPSTk is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published
  by the Free Software Foundation; either version 3.0 of the License, or
  any later version.

  The GPSTk is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with GPSTk; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
  
  This software developed by Applied Research Laboratories at the University of Texas at Austin.
  Copyright 2004-2020, The Board of Regents of The University of Texas System

==============================================================================

==============================================================================

  This software developed by Applied Research Laboratories at the University of
  Texas at Austin, under contract to an agency or agencies within the U.S. 
  Department of Defense. The U.S. Government retains all rights to use,
  duplicate, distribute, disclose, or release this software. 

  Pursuant to DoD Directive 523024 

  DISTRIBUTION STATEMENT A: This software has been approved for public 
                            release, distribution is unlimited.

==============================================================================
"""
import sys
import os
import argparse
import unittest

import gpstk

args = None

def run_unit_tests():
    """A function to run unit tests without using the argument parsing of
    unittest.main() """

    parser = argparse.ArgumentParser(description="Test app for ctest")
    parser.add_argument('-v,--verbose', dest='verbose', action='count',
                        help="Increase the amount of output generated by the program")
    parser.add_argument('-o,--output_dir', dest='output_dir', metavar='dir',
                        help="Path to output directory")
    parser.add_argument('-i,--input_dir', dest='input_dir', metavar='dir',
                        help="Path to root of input data directory")
    global args
    args=parser.parse_args()

    runner=unittest.TextTestRunner()

    # Find all Test classes in the parent script
    script=os.path.basename(sys.argv[0])
    dir=os.path.dirname(sys.argv[0])
    isuite = unittest.TestLoader().discover(dir, pattern=script)

    rc = runner.run(isuite)
    sys.exit(len(rc.failures) + len(rc.errors))
