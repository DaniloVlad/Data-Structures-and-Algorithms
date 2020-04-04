
public class Node {
	
	//Very simple Node for linked list that handles collisions
	//Stores config and next node
	private Configuration config = null;
	private Node next = null;
	
	public Node(Configuration config) {
		//initialize the config
		this.config = config;
	}
		
	//helper function for quick checking
	public boolean hasNext() {
		return (next != null) ? true : false;
	}
	
	//getters/setters for instance variables
	public Configuration getConfig() {
		return config;
	}
	
	//sets next to point to a node
	public void setNext(Node n) {
		if(next == null) 
			next = n;
		else  //if next already set call, next of next.
			next.setNext(n);	
	}
	
	//return next
	public Node getNext() {
		return next;
	}
}
