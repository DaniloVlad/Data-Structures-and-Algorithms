
public class HashDictionary implements DictionaryADT {
	
	//instance vars
	private int modulos = 5023;
	private Node[] table;
	//coprime multiplier
	private static final int exponent = 11;
	
	public HashDictionary() {
		//initialize default object
		table = new Node[modulos];
		modulos = 5023;
	}
	public HashDictionary(int size) {
		//custom table size
		table = new Node[size];
		modulos = size;
	}
	
	//helper hash function
	private int hash(String config) {
		char[] chars = config.toCharArray();
		int hash = chars[0];
		for(int count = 1; count < config.length(); count++) {
			hash = (hash*exponent  + (int) chars[count])%modulos;
		}
		return hash;
	}
	
	//insert config into dict
	public int put(Configuration data) throws DictionaryException {
		int bin = hash(data.getStringConfiguration());
		//config already in dict
		if(getScore(data.getStringConfiguration()) != -1) throw new DictionaryException("Put: config already in dict.");
		//check if collision
		if(table[bin] != null) {
			//solve collision with chaining
			table[bin].setNext(new Node(data));
			return 1;
		}
		//there wasnt any collision
		table[bin] = new Node(data);
		return 0;
	}


	//removes config from dict
	public void remove(String config) throws DictionaryException {
		// TODO Auto-generated method stub
		int bin = hash(config);
		Node root = table[bin];
		if(root == null) throw new DictionaryException("Remove: no data stored at this index");
		//see if the root stores the config
		if(root.getConfig().getStringConfiguration().compareTo(config) == 0)
			table[bin] = root.getNext();
		Node temp = root.getNext();
		//root stores parent, temp stores Node to check
		while(temp != null) {
			Configuration current = temp.getConfig();
			//check to see if configs match
			if(current.getStringConfiguration().compareTo(config) == 0) {
				if(temp.hasNext()) {
					//if there is a next element, set the root to that one
					//removing the current data
					root.setNext(temp.getNext());
					return;
				}
				else {
					//if there is no next element remove the current one from its parent
					root.setNext(null);
					return;
				}
			}
			//work through list
			root = temp;
			temp = temp.getNext();
		}
		
		
	}

	//returns score for given config
	public int getScore(String config) {
		int bin = hash(config);
		Node list = table[bin];
		//if there is data 
		if(list != null)
			//look for config, considering the collisions
			while(list != null) {
				Configuration temp = list.getConfig();
				if(temp.getStringConfiguration().compareTo(config) == 0) return temp.getScore();
				list = list.getNext();
			}
		//config was not found
		return -1;
	}

}
