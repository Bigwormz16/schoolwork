import java.util.Stack;
import java.util.LinkedList;

public class SymbolTable {
	private java.util.Stack<LinkedList<String>> table = new Stack<>();
	
	public void enterScope(){
		table.push(new LinkedList<String>());
		//System.out.println("scope depth: " + table.size());
	}
	
	public void exitScope(){
		table.pop();
	}
	
	public boolean exists(String inputSymbol, int scope){
		// check if symbol exists in specified scope
		int depth = table.size() - 1;
		
		if(scope > depth){
			//System.err.print("blockDepth less than scope");
			return false;
		}
		
		//System.out.println("get(" + (depth - scope) + ")");
		return table.get(depth - scope).contains(inputSymbol);
	}
	
	public boolean existsGlobal(String input){
		return table.get(0).contains(input);
	}
	
	public int search(String inputSymbol){
		for(int i = (table.size() - 1); i >= 0; i--){
			if(table.get(i).contains(inputSymbol)){
				return i;
			}
		}
		
		//otherwise, not found
		return -1;
	}
	
	public boolean insert(String inputSymbol){	
		if(table.get(table.size() - 1).contains(inputSymbol)){
			System.err.println("redeclaration of variable " + inputSymbol);
			return false;
		} else {
			table.get(table.size() - 1).add(inputSymbol);
			//System.out.println("added " + inputSymbol + " to " + (table.size() - 1));
			return true;
		}
	}
}
		
