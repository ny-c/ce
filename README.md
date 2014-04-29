Executables structure
---------------------

CE consists of **check_earthq**, **getearthq** and **qrand** utilities.

**check_earthq** computes how many earthquakes happened when Sun, Mars, Jupiter or Venus were in a
certain position on ecliptic as it visually seen from Earth (astrological positions), then computes
the same value for randomly selected dates. This tool demonstrates that strong earthquakes approx.
3 times more frequent when Earth and the planets are in certain positions relatively to each other.

**getearthq** – puts data from the National Geophysical Data Center / World Data Service: Significant
Earthquake Database (http://www.ngdc.noaa.gov/nndc/struts/form?t=101650&s=1&d=1) to a specified file.

**qrand** – gets random numbers from the Quantum Random Bit Generator Service (http://random.irb.hr/).

Sources structure
-----------------

*check_earthq*, *getearthq* and *qrand* – the executables.

***Static libraries***:

**astro** – top-level astro functionality.

**lists** – tab-delimited files reading.

**random** – random numbers generator; tester.

**swlib32** – Astrodienst Swiss Ephemeris library (http://www.astro.com/swisseph/swephinfo_e.htm?lang=e).

Compiling
---------

**Microsoft Visual Studio 2013** —  you should have Boost libraries installed (http://www.boost.org/).
Specify path to the Boost libraries in BOOST_LIB and BOOST_INC environment variables before compiling.
Open a solution file named src/shdt.sln and choose 'Rebuild solution'.

**GCC/Cygwin** — run 'cmake .', then 'make' in the 'ce' top-level directory.

Running
-------

CMakeLists.txt and Visual Studio project files specify a post-build operation that copies a newly built
executables into a *ce/bin* directory. It contains **main.cfg** and other files needed for the proper
work. Run tools from that directory.