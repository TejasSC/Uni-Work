public class SecretCache
extends Cache
{
  int[] fred;
  boolean[] alice;
  Object[] jim;
  int mary;

  SecretCache(int paramInt1, int paramInt2)
  {
    this.size = paramInt1;
    this.line_size = paramInt2;
    this.fred = new int[this.size / this.line_size];
    this.jim = new Object[this.size / this.line_size];
    this.alice = new boolean[this.size / this.line_size];
    for (int i = 0; i < this.size / this.line_size; i++) {
      this.alice[i] = false;
    }
  }

  public Object cacheSearch(int paramInt)
  {
    int i = paramInt % (2 * this.size) / (this.line_size * 2);
    if ((this.alice[i] != 0) && (this.fred[i] == paramInt / this.line_size))
    {
      this.mary = i;
      return this.jim[i];
    }
    return null;
  }

  public oldCacheLineInfo cacheNewEntry(int paramInt)
  {
    int i = paramInt % (2 * this.size) / (this.line_size * 2);
    oldCacheLineInfo localoldCacheLineInfo = new oldCacheLineInfo();
    localoldCacheLineInfo.old_valid = this.alice[i];
    this.fred[i] = (paramInt / this.line_size);
    this.alice[i] = true;
    localoldCacheLineInfo.data = (this.jim[i] = new Integer(-1));
    return localoldCacheLineInfo;
  }

  public void cacheWriteData(Object paramObject)
  {
    this.jim[this.mary] = paramObject;
  }
}
