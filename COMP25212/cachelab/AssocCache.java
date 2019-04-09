public class AssocCache extends Cache{
  //using cyclic rejection and allocation replacement algorithm

  private int someIndex;
  private int currentIndex;
  private int[] tagList; //Space for tag RAM
  private Object[] entryList; //list of entries/data
  private boolean[] valids; //valid bits represented as booleans

  public AssocCache(int size, int line_size){
    this.size = size;
    this.line_size = line_size;
    int numLines = this.size/this.line_size;
    this.currentIndex = 0;
    //all the size of number of lines in DMC
    this.tagList = new int[numLines];
    this.entryList = new Object[numLines];
    this.valids = new boolean[numLines];
    //initialise all entries as invalid since no entries yet
    for (int n = 0; n < numLines; n++) {this.valids[n] = false;}
  }//AssocCache

  public Object cacheSearch(int addr) {
    int tag = addr/this.line_size;
    int numLines = this.size/this.line_size;
    for (int p = 0; p<numLines; p++) {
      if (this.tagList[p] == tag && this.valids[p]) {
        this.someIndex = p;
        return this.entryList[p];
      }//if
    }//for
    return null;
  }//cacheSearch

  //cyclic rejection and allocation algorithm
  public oldCacheLineInfo cacheNewEntry(int addr) {
    oldCacheLineInfo localOCLI = new oldCacheLineInfo();
    localOCLI.old_valid = this.valids[currentIndex];
    this.tagList[currentIndex] = addr / this.line_size;
    localOCLI.data = (this.entryList[currentIndex] = new Integer(-1));
    this.valids[currentIndex] = true;
    //cycle
    if (currentIndex < this.size/this.line_size - 1) {
      currentIndex++;
    } else {
      currentIndex = 0;
    }//if
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
  }//calculateIndex

}//AssocCache
