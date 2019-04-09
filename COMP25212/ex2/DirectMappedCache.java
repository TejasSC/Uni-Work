public class DirectMappedCache extends Cache{

  private int someIndex; //position of a valid entry
  private int[] tagList; //Space for tag RAM
  private Object[] entryList; //list of entries/data
  private boolean[] valids; //valid bits represented as booleans

  public DirectMappedCache(int size, int line_size){
    this.size = size;
    this.line_size = line_size;
    int numLines = this.size/this.line_size;
    //all the size of number of lines in DMC
    this.tagList = new int[numLines];
    this.entryList = new Object[numLines];
    this.valids = new boolean[numLines];
    //initialise all entries as invalid since no entries yet
    for (int n = 0; n < numLines; n++) {this.valids[n] = false;}
  }

  public Object cacheSearch(int addr) {
    int n = calculateIndex(addr, this.size, this.line_size);
    if (!this.valids[n] && (this.tagList[n] == addr / this.line_size)) {
      this.someIndex = n;
      return this.entryList[n];
    }
    return null;
  }//cacheSearch

  public oldCacheLineInfo cacheNewEntry(int addr) {
    int n = calculateIndex(addr, this.size, this.line_size);
    oldCacheLineInfo localOCLI = new oldCacheLineInfo();
    localOCLI.old_valid = this.valids[n];
    this.tagList[n] = addr / this.line_size;
    localOCLI.data = (this.entryList[n] = new Integer(-1));
    return localOCLI;
  }//oldCacheLineInfo

  @Override
  public void cacheWriteData(Object data) {
    this.entryList[this.someIndex] = data;
  }//cacheWriteData

  //calculates index based on address, size of cache and size of line
  private int calculateIndex(int addr, int cacheSize, int lineSize){
    int numLines = this.size/this.line_size;
    return (addr / this.line_size) % numLines;
  }

}//DirectMappedCache
