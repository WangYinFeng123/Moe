# Moe
GCC 4.9+/Clang 3.6+ (Linux) | MSVC 19.0 (Win 32/64)
--- | ---
[![Travis branch](https://img.shields.io/travis/tonykero/Moe/master.svg?style=flat-square)](https://travis-ci.org/tonykero/Moe) | [![AppVeyor branch](https://img.shields.io/appveyor/ci/tonykero/Moe/master.svg?style=flat-square)](https://ci.appveyor.com/project/tonykero/moe)

[![license](https://img.shields.io/github/license/tonykero/Moe.svg?style=flat-square)](https://github.com/tonykero/Moe/blob/master/LICENSE)

Moe is a C++14 header-only dependency-free [ implementation / framework ] of a Generic Genetic Algorithm

## Quick Overview

The main goal of Moe is to provide a generic and easy way to implement fast solving systems
from any complexity with C++.

Moe stands for Maybe Overpowered Entity, but isn't limited to it.

Moe gives a way for the user to completely define the behavior of the Genetic Algorithm, all parameters are
adjustable, Mutations & Crossovers can be defined and added to Moether in addition to those given by default.

Let's take a look at a base sample using Moe:

```cpp
#include <moe/moe.hpp> // base header to include the Moe library
#include <iostream>

int main()
{
    Moether< Basic GenotypeType > moether;

    moether.setFitnessFunction( [](const Moe< Basic GenotypeType >& moe) -> double
    {
        double fitness = 0.0;
        
        /* increment fitness as moe's fitness grows */
        
        // by calculating error and returning 1/error for example
        // or even returning error and then use moether.setFitnessMode( false );
        // this will sort moes by descending order
        
        return fitness;
    });

    // you can define custom Mutation or Crossover with the 2 following functions
    moether.registerCrossover( std::unique_ptr<Crossover< Basic GenotypeType > > );  // registering a crossover selects it
    moether.registerMutation( std::unique_ptr<Mutation< Basic GenotypeType > > );

    // you can unregister Mutations & Crossovers even those by default
    moether.unregisterCrossover( unsigned int id ); // only relevant for custom-defined crossover
    moether.unregisterMutation( unsigned int id );
    // examples/salesman.cpp uses unregisterMutation()

    moether.setCrossover( /* Crossover ids */ ); // default: moe::Crossover::OnePoint
    // default crossover ids are:
    // moe::Crossover::OnePoint (= 0)
    // moe::Crossover::TwoPoint (= 1)
    // moe::Crossover::Uniform  (= 2)

    moether.setCrossoverEnabled( /* bool */ );  // default: true
    moether.setMutationEnabled( /* bool */ );   // default: true
    
    // a dataset is used to modify genotype of moes
    moether.setDataset( std::vector< genotype basic type > );

    moether.init( /* moes per generation */ , /* elite copies */, /* mutation rate */, /* crossover rate */ );
    // mutation rate (optional): default: 0.1
    // crossover rate(optional): default: 0.5 (applies only on Uniform crossover)

    moether.run( /* number of generations */ );

    // then lastly you retrieve the best element
    Moe best_moe = moether.getBestMoe();

    // now you can retrieve stuff best_moe.genotype & best_moe.fitness
}
```

To understand how registering Mutations and Crossovers works check files 
[Mutations.hpp](https://github.com/tonykero/Moe/blob/master/include/moe/base/Mutations.hpp)
& [Crossovers.hpp](https://github.com/tonykero/Moe/blob/master/include/moe/base/Crossovers.hpp)
and [Moether_defs.hpp Line 7 - 13](https://github.com/tonykero/Moe/blob/master/include/moe/base/Moether_defs.hpp#L7)

### Examples

Examples can be found [here](https://github.com/tonykero/Moe/tree/master/examples)

## Features

Moe contains the following features:

* Crossovers:
    * One Point
    * Two Point
    * Uniform
    * User-defined

* Mutations:
    * Substitution
    * Insertion
    * Deletion
    * Translocation
    * User-defined

* Elitism

* Genetic Representation:
    * Explicit representation
    * User-defined

* Performance:
    * Parallel Implementation ( not yet )

* Adaptive GA Variant ( not yet )

## Building

Moe uses CMake, options are available:

Options         | Description                   | Default Value |
--------------- | ----------------------------- | ------------- |
BUILD_EXAMPLES  | build examples                | ON            |
DEBUG           | Enable debugging symbols      | OFF           |

Moe was successfully tested against:
* GCC:
    * 4.9 (4.9.4)
    * 5 (5.4.1)
    * 6 (6.2)
    * MinGW:
        * GCC 5.3
* Clang:
    * 3.6 (3.6.2)
    * 3.7 (3.7.1)
    * 3.8 (3.8.0)
    * 3.9 (3.9.1)
* MSVC:
    * 19.0 ( Visual Studio 14 2015 )

Compiling:

```
git clone https://github.com/tonykero/Moe.git
cd Moe
mkdir build && cd build && cmake .. && cmake --build .
```
builds Moe with examples

## License

[The MIT License](https://opensource.org/licenses/MIT)
