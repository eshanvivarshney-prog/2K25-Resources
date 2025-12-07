%nproc=2
%mem=2GB
#HF STO-3G opt freq

Ethene

0 1
C1
C2 1 1.3
H3 1 1.0 2 120.0
H4 1 1.0 2 120.0 3 180.0
H5 2 1.0 1 120.0 3 0.0
H6 2 1.0 1 120.0 5 180.0

