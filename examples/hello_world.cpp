#include <moe/moe.hpp>
#include <iostream>
#include <chrono>

int main()
{
    Moether<Moe> moether;
    std::string target = "hello world";

    moether.setFitnessFunction( [target](const Moe& moe) -> double
    {
        std::string genotype = moe.getGenotype();

        int             dSize   = target.size() - genotype.size();
        unsigned int    min     = std::min(target.size(), genotype.size()),
                        error   = std::abs(dSize) * 256; // add 256 error points for each extra or lack of char

        for(unsigned int i = 0; i < min; i++)
            error += std::abs( genotype[i] - target[i] );
        
        return error;
    });

    moether.setFitnessMode( false );                // fitness by scoring error
    moether.setMaxGenotypeSize( target.size() );    // adapts the size of the genotype
    moether.setCrossover( moe::Crossover::Uniform );

    auto start = std::chrono::high_resolution_clock::now();

        moether.init( 200 , 40 );
        moether.run( 500 );

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> diff = end-start;

    std::cout   << "genotype: " << moether.getBestMoe().getGenotype() << "\n"
                << "fitness: " << moether.getBestMoe().getFitness() << "\n"
                << "time spent: " << diff.count() << " seconds" << std::endl;
}