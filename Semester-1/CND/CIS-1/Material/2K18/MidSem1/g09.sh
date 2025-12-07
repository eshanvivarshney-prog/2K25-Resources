#!/bin/bash
#SBATCH -A cn4101
#SBATCH --qos=cn4101
#SBATCH -n 2
#SBATCH -N 1
#SBATCH --mem-per-cpu=200
#SBATCH --time=03:00:00

module load Gaussian/09revC
export GAUSS_SCRDIR=/scratch/$USER.$SLURM_JOBID
/bin/mkdir -p $GAUSS_SCRDIR

g09 formic_monomer.com

/bin/rm -rf $GAUSS_SCRDIR

