

// Note that when using this scanf will not accept extra whitespace at the start
// this generally means that it is necessary to read the previous \n character
// I could fix this to deal with this case but I do not want to break any code
// relying on this.
// see new_string_helper for a slightly better engineered solution
char* get_next_string(){
  static char buf[26] = {0};
  char x = '-';
  if(scanf("\"%25[^\"]\"%c",buf,&x)==0){
	printf("Failed to read next string\n");
	exit(-1);
  }
  int len = strlen(buf);
  char* ret = malloc(sizeof(char)*(len+1));
  strcpy(ret,buf);
  return ret;
}

