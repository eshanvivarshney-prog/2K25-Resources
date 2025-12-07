# Enhanced Sampling Techniques:

## 1.  Replica Exchange MD
	    
Here we exchange configs at different temperatures [given they satisfy some criteria] after a set number of time steps, to attempt to cover more ground and be able to figure out the lowest energy config.
	
Configs at higher temperatures eventually find their way into lower temperature simulations, thus increasing the variety of configs being simulated and allowing a greater sample size of configs.
	
Refer Fig. 1 on _https://www.publish.csiro.au/ch/pdf/CH21120_
	
This method allows us to calculate any thermodynamic property with great accuracy :D
	
Problem:
Since we're swapping 2 replicas at different temperatures, in most cases the energy graphs are discontinuous. They have no connection to each other, and thus we cannot calculate parameters such as activation energies [or anything related to kinetics at all!]
		

## 2. Umbrella Sampling
	
This exists to tackle a problem faced by systems with insuffiecient sampling [e.g. Na+ and Cl- in water]. 

Consider Na+ and Cl- in water:
Any simulation run on the system, regardless of where the ions start, will almost immediately get to the state where the NaCl lattice is formed [as that has much lower energy than solvated ions]

Take a simulation starting at R = 10 Angstroms, where R is the distance between Na and Cl ions. The ions will almost immediately move towards each other to form a bond/lattice.

Thus we have almost insignificant sampling for the R = 10 Angstrom case, which throws off our probability distribution. And since we use the probability distribution to calculate delta G, this gives us an almost infinite value of delta G for R = 10 Angstroms (as probability -> 0)

    Delta G = -RT ln(probability)  

To counter this, we introduce inverted "umbrella" of harmonic potential energy (basically parabola which is concave up) at the desired R value to trap the Cl ion in this potential well. This is just another addition to the Force Field equation we made for the MD, and we can compensate for its effects on the PE graph later on

Now we can do some 'n' extra simulations with a different harmonic potential well each time, at such values of R as our need requires (i.e. such that we get adequate sampling across the region)

If the potential is added at R = x1, x2, x3, x4 ... in our simulations, we add the energy terms to the force field eqn as 

    E(harmonic) = (1/2) * k * ((R - xi) ^ 2); i = 1, 2, 3, ...

### Eg. Question: What is the free energy surface of butane w.r.t conformational changes?
Ans: We measure the time spent by a single butane molecule in any conformational state and using the fact that the probability of butane molecules being proportional to (a) the time a single molecule spends in that state, and (b) the fraction of molecules in a bulk which are in that state. 
    
Thus we arrive at a probability distribution, and then free energy is basically inversely proportional to the log of probability

### Now for NaCl:

The Na and Cl ions immediately move close to each other and form a lattice in almost negligible time, thus the probability we get of them being some radius apart tends to zero as the radius increases. This implies the delta G graph tends to infinity (which is not true). 

Now we apply umbrella sampling, and we get almost equal sampling throughout the range of R that we have

But the problem is, now the probabilities are affected by this harmonic potential, this bias. Thus what we can do is for each umbrella, we look at the probability function of just that region and check if it's shifted to the left or the right (thus telling us how the true potential energy changes, whether it increases or decreases). Magnitude of the slop of the PE graph can be estimated using how shifted the probability is wrt the xi

Thus now we have discontinuous accurate-ish probability curves for each region separately. Problem is, in this way we have 2 probabilities (and thus 2 free energies) for the points at which graph is discontinuous. So we can change the positions of the curves and "stitch" them together and bring them all into a continuous function. But problem is that we don't know where exactly does the entire graph go? Which is the reason why we don't measure absolute free energy, but rather delta G. We can just set the initial probability to zero and measure change in G (delta G) after that

### Problem:
We need to know what our reaction coordinate is!!!

## 3. Metadynamics

In a typical PES, there is an energy barrier b/w the final and initial states which makes the change very slow. What we can do is add some special Gaussian functions to the PES to "raise up" the minimas and thus make is much faster for the state to change b/w initial and final

#### Analogy:
It's basically like adding stones to a well of water to bring up the water level.
The number/volume of stones we put in basically gives us the work done in raising the energy levels.

# _Today's Scenario:_

We use this thingamabobbo called

## Hybrid QM/MM Calculations:

Eg. we have R + A -------> P + B in presence of some enzyme (protein)

When a very large system involves bond breaking/forming, we are forced to use hybrid QM/MM, where the QM models the bond breaking/forming and the MM part models the rest of the protein

So what we do is have a "QM region" and "MM region" where we calculate energies separately

- QM region -> reactant/product + protein's binding site only

- MM region -> rest of the protein + water box

#### Problems
* We haven't accounted for the interaction b/w the QM and MM regions, and the bonds that we cut while drawing the boundaries for the QM region

To solve this:

E(net) = E(system, MM) + E(QM, QM) - E(QM, MM)