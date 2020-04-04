
public class BinaryNode {
	
	private Pixel value;
	private BinaryNode left, right, root;
	//init empty node
	public BinaryNode() {
		this.value = null;
		this.left = null;
		this.right = null;
		this.root = null;
	}
	//data node
	public BinaryNode(Pixel value, BinaryNode left, BinaryNode right, BinaryNode parent) {
		this.root = parent;
		this.value = value;
		this.left = left;
		this.right = right;
		
	}
	//getters/setters
	public void setParent(BinaryNode par) {
		this.root = par;
	}
	
	public void setLeft(BinaryNode p) {
		this.left = p;
	}
	
	public void setRight(BinaryNode p) {
		this.right = p;
	}
	
	public void setData(Pixel value) {
		this.value = value;
	}
	
	public boolean isLeaf() {
		return this.value == null;
	}
	
	public Pixel getData() {
		return this.value;
	}
	
	public BinaryNode getLeft() {
		return this.left;
	}
	
	public BinaryNode getRight() {
		return this.right;
	}
}
