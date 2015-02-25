#include<bits/stdc++.h>

using namespace std;

int isprefix(string str1,string str2){
	int i,m=str1.length(),n=str2.length();

	if(m>n)
		return 0;

	for(i=0;i<m;i++)
		if(str1[i]!=str2[i])
			break;

	if(i==m)
		return 1;
	else
		return 0;
}

int main(){
	
	int count=1,mode;
	FILE *dataset=fopen("Dataset.txt","r"),*stopwords=fopen("Stopwords.txt","r");
	FILE *inv=fopen("InvertedIndex.txt","w"),*perm=fopen("PermuteTermIndex.txt","w");

	map<string, set<int> > invertedIndex;
	map<string, string> permuteIndex;
	set<string> permuteTerms;

	printf("Enter mode: ");
	scanf("%d",&mode);

	while (true) {
    	char buf[1000],c;
    	
    	if(fscanf(dataset,"%s%c",buf,&c)==EOF) 
    		break;

    	string str(buf);

    	if(invertedIndex.find(str)==invertedIndex.end())
    		invertedIndex[str]= set<int>();
    	invertedIndex[str].insert(count);
    	if(c=='\n')
    		count++;
	}
	fclose(dataset);

	while (true) {
    	
    	char buf[1000],c;
    	
    	if(fscanf(stopwords,"%s%c",buf,&c)==EOF) 
    		break;

    	int n=strlen(buf);
    	if(buf[n-1]==',')
    		buf[n-1]='\0';

    	string str(buf);

    	if(invertedIndex.find(str)!=invertedIndex.end())
    		invertedIndex.erase(str);
	}
	fclose(stopwords);

	map<string, set<int> >::iterator it;
	set<int>::iterator sit;

	for(it=invertedIndex.begin();it!=invertedIndex.end();it++){

			fprintf(inv,"%s",(it->first).c_str());

			for(sit= it->second.begin();sit!=it->second.end();sit++)
				fprintf(inv," %d",*sit);
			fprintf(inv,"\n");

			string str(it->first);
			
			str.push_back('$');
			int n=str.length();

			char buf[1000];

			for(int i=0;i<n;i++){
				count=0;
				for(int j=i;j<n;j++)
					buf[count++]=str[j];
				for(int j=0;j<i;j++)
					buf[count++]=str[j];

				buf[count]='\0';

				string str1(buf);
				permuteIndex[str1]=it->first;
				permuteTerms.insert(str1);
				fprintf(perm,"%s %s\n",buf,(it->first).c_str());
			}
	}

	fclose(inv);
	
	printf("Open InvertedIndex.txt & PermuteTermIndex.txt to see the output\n");

	if(mode==2){
		char buf[100],query[100];
		int i;
		count=0;
		printf("Enter query: ");
		scanf("%s",buf);
		int n=strlen(buf);

		buf[n++]='$';
		buf[n]='\0';

		for(i=0;i<n;i++)
			if(buf[i]=='*')
				break;

		for(int j=i+1;j<n;j++)
			query[count++]=buf[j];

		for(int j=0;j<i;j++)
			query[count++]=buf[j];

		query[count]='\0';

		string str(query);
		set<int> ans;

		set<string>::iterator it=lower_bound(permuteTerms.begin(),permuteTerms.end(),str);
		set<int>::iterator sit;

		while(it!=permuteTerms.end()){
			

			if(isprefix(str,*it)){
				string str1=permuteIndex[*it];
				for(sit=invertedIndex[str1].begin();sit!=invertedIndex[str1].end();sit++)
					ans.insert(*sit);
			}
			else
				break;
			it++;

		}

		count=1;
		dataset=fopen("Dataset.txt","r");
		FILE *docs=fopen("RetrievedDocuments.txt","w");
		while (true) {
    		char buf[1000];
    	
    		if(fscanf(dataset," %[^\n]s",buf)==EOF) 
    			break;

    		if(ans.find(count)!=ans.end())
    			fprintf(docs,"%s\n",buf);
    		count++;
    	}
    	printf("Open RetrievedDocuments.txt to see the output\n");
	}

	return 0;
}
