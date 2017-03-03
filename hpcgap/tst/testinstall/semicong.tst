#############################################################################
##
#W  semicong.tst                 GAP library                Robert F. Morse
##
##
#Y  Copyright (C)  1996,  Lehrstuhl D für Mathematik,  RWTH Aachen,  Germany
##
gap> START_TEST("semicong.tst");
gap> #######################################################################
gap> ##
gap> ##  1. Testing infinite finitely presented commutative semigroups 
gap> ##     generated by n elements s_1, ... s_n with relations
gap> ##     of the form s_i^{i+1}=s_i for i=1,...,n-1, and s_i*s_n = s_i 
gap> ##
gap> ##  For congruences generated by the torsion elements we have
gap> ##  full closure.   
gap> ##
gap> ##  The following are tests for n=3 
gap> #######################################################################
gap> n:=3;;
gap> f := FreeSemigroup(n);;
gap> gns := GeneratorsOfSemigroup(f);;
gap> rel := [];;
gap> x:=0;;
gap> for x in [1..Length(gns)-1] do
> Append(rel,List(gns,y->[gns[x]*y,y*gns[x]]));
> Add(rel,[gns[x]^(x+1),gns[x]]);
> Add(rel,[gns[x]*gns[Length(gns)],gns[x]]);
> Add(rel,[gns[Length(gns)]*gns[x],gns[x]]);
> od;
gap> s := f/rel;;
gap> sgns := GeneratorsOfSemigroup(s);;
gap> c := SemigroupCongruenceByGeneratingPairs(s,[[sgns[1],sgns[2]]]);;
gap> EquivalenceRelationPartition(c);;
gap> ##   
gap> ## Check to see if elements are in the partition
gap> ##     true and false
gap> ##
gap> ec := EquivalenceClassOfElement(c,sgns[n]);;
gap> Size(ec);
1
gap> ec := EquivalenceClassOfElement(c,sgns[n-1]);;
gap> sgns[n] in ec;
false
gap> Size(ec);
5
gap> ######################################################################
gap> ## 2. Check partital closure of an infinite block
gap> ##    
gap> ##    The semigroup has two generators, is commutative and has
gap> ##    two blocks. One finite the other infinite.
gap> ##    
gap> ##    <a,b>/[a^3=a, a*b=a, b*a=a]
gap> ## 
gap> ######################################################################
gap> f :=FreeSemigroup(2);; 
gap> s := f/[[f.1^3,f.1],[f.1*f.2,f.1],[f.2*f.1,f.1]];; 
gap> gns := GeneratorsOfSemigroup(s);; 
gap> c:=
> SemigroupCongruenceByGeneratingPairs(s,[[gns[1],gns[1]^2],[gns[2],gns[2]^2]]);;
gap> ec :=EquivalenceClassOfElement(c,gns[2]);; 
gap> gns[2]^20 in ec;
true
gap> gns[2]^40 in ec;
true
gap> ##
gap> ## We should never get a full closure
gap> ##
gap> HasEquivalenceRelationPartition(c);
false
gap> ######################################################################
gap> ## 3. Check partital closure with an infinite number of blocks
gap> ##
gap> ##    Create a congruence with an infinite number of blocks
gap> ## 
gap> ######################################################################
gap> f :=FreeSemigroup(2);; #<a,b>
gap> s := f/[[f.1^3,f.1],[f.1*f.2,f.2*f.1]];; # a^3=a, a*b=b*a
gap> gns := GeneratorsOfSemigroup(s);; #<a,b>
gap> c := SemigroupCongruenceByGeneratingPairs(s,[[gns[1],gns[1]^2]]);;
gap> ec :=EquivalenceClassOfElement(c,gns[1]*gns[2]^20);;
gap> gns[1]^2*gns[2]^20 in ec;
true
gap> ######################################################################
gap> ## 4. Compute some quotient semigroups and compute some finite
gap> ##    congruences of these quotient semigroups.  
gap> ## 
gap> ######################################################################
gap> f := FreeSemigroup("a","b","c");; a:= f.1;; b:=f.2;; c:=f.3;; 
gap> s := f/[[a^5,a],[b^10,b],[a*b,a],[b*a,a],[c*b,b],[b*c,b],[c*a,a],[a*c,a]];;
gap> sng:=GeneratorsOfSemigroup(s);;
gap> c := SemigroupCongruenceByGeneratingPairs(s,[[sng[1],sng[1]^2]]);;
gap> ec := EquivalenceRelationPartition(c);;
gap> s1:=s/c;;
gap> sng1 := GeneratorsOfSemigroup(s1);;
gap> c := SemigroupCongruenceByGeneratingPairs(s1,[[sng1[1],sng1[1]^2]]);; 
gap> EquivalenceRelationPartition(c);
[  ]
gap> c := SemigroupCongruenceByGeneratingPairs(s1,[[sng1[2],sng1[2]^2]]);;
gap> ec:=EquivalenceRelationPartition(c);;
gap> Size(ec);
1
gap> Size(ec[1]);
9
gap> STOP_TEST( "semicong.tst", 890000);

#############################################################################
##
#E
