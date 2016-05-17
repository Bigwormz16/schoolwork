/* *** This file is given as part of the programming assignment. *** */
public class Parser {


    // tok is global to all these parsing methods;
    // scan just calls the scanner's scan method and saves the result in tok.
    private Token tok; // the current token
    private int blockDepth = -1; //init at -1 so that 0 will be global depth
    private SymbolTable table;
    
    private void scan() {
	tok = scanner.scan();
    }

    private Scan scanner;
    Parser(Scan scanner) {
	this.scanner = scanner;
	this.table = new SymbolTable();
	scan();
	program();
	if( tok.kind != TK.EOF )
	    parse_error("junk after logical end of program");
    }
    
    private void addSymbol(String sym){
    	//add a variable to the symbol table
    	if(is(TK.ID)){
    		//need to use 'is' so that TK doesnt get munched
    		if(table.insert(sym) == true){
    			//dont redeclare in C
	   		System.out.println("int x" + sym + "_" + blockDepth + ";"); //::c code:: variable dec
	   	}
    		scan();
    	} else {
    		mustbe(TK.ID); //display error msg
    	}
    }
    
    private int lookupSymbol(String sym){
    	//check if a symbol is in the table (ALL SCOPES)
    	int depth = table.search(sym); //returns depth of var if found
    	if(depth > -1){
    		//symbol found in current scope
    		return depth;
    	} else {
    		//not found
    		System.err.println(tok.string + " is an undeclared variable on line " + tok.lineNumber);
    		System.exit(1);
    	}
    	return -1;
    }
    
    private void scopedLookup(String sym, int scope){
        //check if a symbol exists in a specified scope
    	//scope == -1 specifies global scope
    	
    	//bool to hold lookup result
    	boolean result = false;
    	
    	if(scope == -1){
    		//global scope
    		result = table.existsGlobal(sym);
    	} else {
    		result = table.exists(sym, scope);
    	}
    	
    	if(result == false){
    		if(scope == -1){
    			//dont print a number if global scope
    			System.err.println("no such variable ~" + sym + " on line " + tok.lineNumber);
    		} else {
    			System.err.println("no such variable ~" + scope + sym + " on line " + tok.lineNumber);
    		}
    		
    		System.exit(1);
    	}
    }

    private void program() {
    	System.out.println("#include <stdio.h>"); //::c code:: necessary for printf to function
    	System.out.println("int main()"); //::c code::
	block();
//    	System.out.println("}"); //::c code::
    }

    private void block(){
    	blockDepth++;
    	table.enterScope();
	System.out.println("{"); //::c code::
    
	declaration_list();
	statement_list();
	
	System.out.println("}"); //::c code::
	table.exitScope();
	blockDepth--;
    }

    private void declaration_list() {
	// below checks whether tok is in first set of declaration.
	// here, that's easy since there's only one token kind in the set.
	// in other places, though, there might be more.
	// so, you might want to write a general function to handle that.
	while( is(TK.DECLARE) ) {
	    declaration();
	}
    }

    private void declaration() {
    	//code generated in addSymbol func
	mustbe(TK.DECLARE);
	//mustbe(TK.ID);
	
	addSymbol(tok.string);
	
	while( is(TK.COMMA) ) {
	    scan();
	    //mustbe(TK.ID);
	    addSymbol(tok.string);
	}
    }

    private void statement_list() {
	while(isStatement()){
		statement();
	}
	// . . .
    }

    private boolean isStatement(){
	//peek at first set to
    	//determine if token is statement
	if(is(TK.PRINT) ||
	   is(TK.DO)    ||
	   is(TK.IF)    ||
	   is(TK.TILDE) ||
	   is(TK.ID)    ){
		return true;
	} else {
		return false;
	}
    }

    private void statement(){
	if(is(TK.PRINT)){
		parse_print();
	} else if(is(TK.DO)){
		parse_do();
	} else if(is(TK.IF)){
		parse_if();
	} else if(is(TK.TILDE) || is(TK.ID)){
		assignment();
	}
    }

    private void assignment(){
	ref_id();
	mustbe(TK.ASSIGN);
    	System.out.print(" = "); //::c code::
	expr();
	System.out.println(";"); //::c code::
    }

    private void parse_print(){
	mustbe(TK.PRINT);
	System.out.print("printf(\"%d\\n\", "); //::c code::
	expr();
	System.out.println(");"); //::c code::
    }

    private void parse_do(){
	mustbe(TK.DO);
	System.out.print("while("); //::c code::
	guarded_command();
	mustbe(TK.ENDDO);
	//System.out.println("}"); //::c code::
    }

    private void parse_if(){
	mustbe(TK.IF);
	System.out.print("if("); //::c code::
	guarded_command();
	while(is(TK.ELSEIF)){
		System.out.print("else if("); //::c code::
		scan();
		guarded_command();
	}

	if(is(TK.ELSE)){
		System.out.print("else"); //::c code::
		scan();
		block();
	}

	mustbe(TK.ENDIF);
		
    }

    private void guarded_command(){
	expr();
    	System.out.print(" <= 0)"); //::c code:: true if non-positive, false if positive
	mustbe(TK.THEN);
	block();
    }

    private void expr(){
	term();
	while(is(TK.PLUS) || is(TK.MINUS)){
	    	System.out.print(" " + tok.string + " "); //::c code:: + or - signs
	    	scan();
		term();
	}
    }

    private void term(){
	factor();
	while(is(TK.TIMES) || is(TK.DIVIDE)){ // TODO: change multop
	    	System.out.print(" " + tok.string + " "); //::c code:: * or / signs
		scan();
		factor();
	}
    }

    private void factor(){
	if(is(TK.LPAREN)){
		System.out.print("("); //::c code::
		scan();
		expr();
		mustbe(TK.RPAREN);
		System.out.print(")"); //::c code::
	} else if(is(TK.TILDE) || is(TK.ID)){
		ref_id();
	} else if(is(TK.NUM)){
		System.out.print(tok.string); //::c code::
		scan();
	}
    }

    private void ref_id(){
    	//System.out.println("rGot this: " + tok.string);
	if(is(TK.TILDE)){
		int scope = -1;
		scan();
		
		//System.out.println("~Got this: " + tok.string);
		if(is(TK.NUM)){
			scope = Integer.parseInt(tok.string);
			//System.out.println("Got scope: " + scope);
			scan();
		}
		scopedLookup(tok.string, scope);
		if(scope == -1){
			System.out.print("x" + tok.string + "_0"); //::c code:: global
		} else {
			//blockDepth = 1, ~1var would want xvar_0
			//blockDepth = 2, ~1var would want xvar_1
			System.out.print("x" + tok.string + "_" + (blockDepth - scope)); //::c code::
		}
	} else {
		//no tilde ~> normal lookup
		int depth = lookupSymbol(tok.string);
		System.out.print("x" + tok.string + "_" + depth); //::c code::
	}
	scan();
    }

    // is current token what we want?
    private boolean is(TK tk) {
        return tk == tok.kind;
    }

    // ensure current token is tk and skip over it.
    private void mustbe(TK tk) {
	if( tok.kind != tk ) {
	    System.err.println( "mustbe: want " + tk + ", got " +
				    tok);
	    parse_error( "missing token (mustbe)" );
	}
	scan();
    }

    private void parse_error(String msg) {
	System.err.println( "can't parse: line "
			    + tok.lineNumber + " " + msg );
	System.exit(1);
    }
}
