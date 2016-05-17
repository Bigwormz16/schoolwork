#testing for loops - basic functionality test
# for loops are defined as:
# for ::= '{' assignment ':' number ':' block '}'
@counter

{counter=0: 5 :!counter} #output should print 0 through 4
	
!counter # should print 5 (var still in scope [loop was broken by condition 5<5])
