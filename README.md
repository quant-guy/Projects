# Welcome!

Weclome to my humble collection of AI and Math tools.  The inspiration for
this project is to have a self contained suite of tools for personal use
or for use in research.  Feel free to manipulate these libraries or to 
redistribute them, just make sure you include the licensing agreement and
my name in there somewhere.  I've even started a 'MyProject' directory to 
help you get started.

The only thing I ask is that if you use these libraries for commercial
purposes, please reach out to me first to negotiate a reasonable licensing
fee.

# Introduction 

A little backstory about these projects...

Frustrated with the tools out there at the time (I started this collection
sometime around 2009), I decided to write my own.  I find third party 
dependencies a bane of frustration so I've kept them at an absolute minimum.

AI and Math have been my passion all my life, so these libraries were created
to facilitate my work and personal research.  I hope you can get some use 
out of them as well

# Platforms

I've tried to keep these cross platform, but I run Ubuntu Linux, so I only 
test on that platform.

# Paradigms

I leverage C++ coding paradigms when possible.  The nature of the material
seems to suggest an object approach, so I've taken advanatage of the tools
C++ has provided e.g. inheritance, templates, etc.  I've tried to keep 
everything self contained enough that you don't need to muck around with 
template classes and such if its not your thing.

# Requirements

- Windows, Mac OS X or Ubuntu Linux (I've tested on Linux ONLY)
- g++
- make
- cmake

# Building

> cmake .
> make

# Contents

The `Projects` directory contains the following major projects:

- AILib - collection of AI and ML Libraries
- MathLib - collection of Math Libraries referenced by AILib
- MyProject - sample project to start our own project under this framework 
- Utility - utilities referenced by all of the above

## AILib

Contains the following:

- Genetics - framework for template coded Genetic Algorithms
- Cluster - various Clustering Algorithms
- NeuralNetworks - extremely low latency Neural Networks

## MathLib

Contains the following:

- ActivationFunctions - Activation Functions such as tanh, etc.
- Fourier - Fourier Analysis package
- Matrix - low latency Matrix functionality 
- Metrics - math functions for various metrics
- Random - random number generation
- Statistics - statistical functions


