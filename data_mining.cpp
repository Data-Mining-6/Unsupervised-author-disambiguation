#include <bits/stdc++.h>
#define NO_OF_SAMPLE 100000
#define DATA_FILE_NAME "data_set_aminar_dblp.v11/dblp_papers_v11.txt"
//#define DATA_FILE_NAME "data_set_aminar_dblp.v11/sample_of_dblp_papers_v11.txt"

using namespace std;

class Authors
{
	public :
		string name;
		string id;
		string org;

		Authors();
};

class Venue
{
	public :
		string id;
		string raw;

		Venue();
};

class Fos
{
	public :
		string name;
		double w;

		Fos();
};

class Word_index
{
	public :
		string word;
		vector<string> index;

		Word_index();
};

class Indexed_abstract
{
	public :
		int IndexLength;
		vector<Word_index> InvertedIndex;

		Indexed_abstract();
};

class Paper
{
	public :
		string id;
		string title;
		list<Authors> authors;
		Venue venue;
		int year;
		list<string> keywords;
		list<Fos> fos;
		list<string> references;
		int n_citation;
		string page_start;
		string page_end;
		string doc_type;
		string lang;
		string publisher;
		string volume;
		string issue;
		string issn;
		string isbn;
		string doi;
		string pdf;
		list<string> url;
		string abstract;
		Indexed_abstract indexed_abstract;

		Paper();
};

class Collection
{
	public :
		int collection_size;
		vector<Paper> paper;
		map<string, int> attributes;

		Collection();
		void read_data();
		void print_data();
		void map_attributes_to_integer();
};

string get_next_word(string this_paper, int *j)
{
	string this_word;
	while(((*j) < this_paper.size()) && (this_paper[(*j)] != '"'))
	{
		(*j)++;
	}
	(*j)++;
	while(((*j) < this_paper.size()) && (this_paper[(*j)] != '"'))
	{
		this_word.push_back(this_paper[(*j)]);
		(*j)++;	
	}
	(*j)++;
	return this_word;
}

ifstream input_file;

int main()
{
	input_file.open(DATA_FILE_NAME);
	if(!input_file)
	{
		cout<<"Error!, Couldn't able to open the file."<<endl;
		return 0;
	}
	Collection collection;
	collection.read_data();
	//collection.print_data();
	input_file.close();
	return 0;
}

Authors :: Authors()
{
	name = "";
	id = "";
	org = "";
}

Venue :: Venue()
{
	id = "";
	raw = "";
}

Word_index :: Word_index()
{
	word = "";
	index.resize(0);
}

Fos :: Fos()
{
	name = "";
	w = 0.0;
}

Indexed_abstract :: Indexed_abstract()
{
	IndexLength = 0;
	InvertedIndex.resize(0);
}

Paper :: Paper()
{
	id = "";
	title = "";
	authors.resize(0);
	year = 0;
	keywords.resize(0);
	fos.resize(0);
	references.resize(0);
	n_citation = 0;
	page_start = "";
	page_end = "";
	doc_type = "";
	lang = "";
	publisher = "";
	volume = "";
	issue = "";
	issn = "";
	isbn = "";
	doi = "";
	pdf = "";
	url.resize(0);
	abstract = "";
}

Collection :: Collection()
{
	collection_size = NO_OF_SAMPLE;
	paper.resize(NO_OF_SAMPLE);
	map_attributes_to_integer();
}

void Collection :: print_data()
{
	for(int i = 0; i < collection_size; i++)
	{
		cout<<"id : "<<paper[i].id<<endl;
		cout<<"title : "<<paper[i].title<<endl;
		cout<<"authors : "<<endl;
		for(auto x : paper[i].authors)
		{
			cout<<'\t'<<"name : "<<x.name;
			cout<<'\t'<<"id : "<<x.id;
			cout<<'\t'<<"org : "<<x.org<<endl;
		}
		cout<<"keywords : "<<endl;
		for(auto x : paper[i].keywords)
		{
			cout<<'\t'<<x<<endl;
		}
		cout<<"fos : "<<endl;
		for(auto x : paper[i].fos)
		{
			cout<<'\t'<<"name : "<<x.name;
			cout<<'\t'<<"w : "<<x.w<<endl;
		}
		cout<<"references : "<<endl;
		for(auto x : paper[i].references)
		{
			cout<<'\t'<<x<<endl;
		}
		cout<<"venue : "<<endl;
		cout<<'\t'<<"raw : "<<paper[i].venue.raw<<endl;
		cout<<'\t'<<"id : "<<paper[i].venue.id<<endl;
		cout<<"year : "<<paper[i].year<<endl;
		cout<<"n_citation : "<<paper[i].n_citation<<endl;
		cout<<"page_start : "<<paper[i].page_start<<endl;
		cout<<"page_end : "<<paper[i].page_end<<endl;
		cout<<"doc_type : "<<paper[i].doc_type<<endl;
		cout<<"lang : "<<paper[i].lang<<endl;
		cout<<"publisher : "<<paper[i].publisher<<endl;
		cout<<"volume : "<<paper[i].volume<<endl;
		cout<<"issue : "<<paper[i].issue<<endl;
		cout<<"issn : "<<paper[i].issn<<endl;
		cout<<"isbn : "<<paper[i].isbn<<endl;
		cout<<"doi : "<<paper[i].doi<<endl;
		cout<<"pdf : "<<paper[i].pdf<<endl;
		cout<<"url : "<<endl;
		for(auto x : paper[i].url)
		{
			cout<<'\t'<<x<<endl;
		}
		cout<<"indexed_abstract : "<<endl;
		cout<<'\t'<<"IndexLength : "<<paper[i].indexed_abstract.IndexLength<<endl;
		cout<<'\t'<<"InvertedIndex : "<<endl;
		for(auto x : paper[i].indexed_abstract.InvertedIndex)
		{
			cout<<"\t\t"<<"word : "<<x.word<<"\t\tIndex : ";
			for(auto y : x.index)
			{
				cout<<y<<",";
			}
			cout<<"\n";
		}
		cout<<endl;
	}
}

void Collection :: read_data()
{
	for(int i = 0; i < collection_size; i++)
	{
		string this_paper;
		getline(input_file, this_paper);
		if(this_paper == "")
		{
			cout<<"Only "<<i<<" papers are present in given file."<<endl;
			paper.resize(i);
			collection_size = i;
			break;
		}
		int j = 0;
		while(j < this_paper.size())
		{
			string this_word = get_next_word(this_paper, &j);
			auto it = attributes.find(this_word);
			if(it != attributes.end())
			{
				int key = it->second;
				switch(key)
				{
					case 0 : 	paper[i].id = get_next_word(this_paper, &j);
								break;

					case 1 :	paper[i].title = get_next_word(this_paper, &j);
								break;

					case 2 :	do
								{
									Authors temp;
									do
									{
										string temp1 = get_next_word(this_paper, &j);
										if(temp1 == "name")
										{
											temp.name = get_next_word(this_paper, &j);
										}
										else if(temp1 == "id")
										{
											temp.id = get_next_word(this_paper, &j);
										}
										else if(temp1 == "org")
										{
											temp.org = get_next_word(this_paper, &j);
										}
									}while((j < this_paper.size()) && (this_paper[j] != '}'));
									paper[i].authors.push_back(temp);
								}while((j < this_paper.size()) && (this_paper[j + 1] != ']'));
								break;

					case 3 :	do
								{
									string temp1 = get_next_word(this_paper, &j);
									if(temp1 == "id")
									{
										paper[i].venue.id = get_next_word(this_paper, &j);
									}
									else if(temp1 == "raw")
									{
										paper[i].venue.raw = get_next_word(this_paper, &j);
									}
								}while((j < this_paper.size()) && (this_paper[j] != '}'));
								break;

					case 4 :	j = j + 2;
								paper[i].year = 0;
								while((j < this_paper.size()) && (this_paper[j] >= '0') && (this_paper[j] <= '9'))
								{
									paper[i].year *= 10;
									paper[i].year += (this_paper[j] - '0');
									j++;
								}
								break;

					case 5 :	do
								{
									string temp1 = get_next_word(this_paper, &j);
									paper[i].keywords.push_back(temp1);
								}while((j < this_paper.size()) && (this_paper[j] != ']'));
								break;

					case 6 :	do
								{
									Fos temp;
									do
									{
										string temp1 = get_next_word(this_paper, &j);
										if(temp1 == "name")
										{
											temp.name = get_next_word(this_paper, &j);
										}
										else if(temp1 == "w")
										{
											j = j + 2;
											temp.w = 0;
											int flag = 0;
											while((j < this_paper.size()) && (((this_paper[j] >= '0') && (this_paper[j] <= '9')) || (this_paper[j] == '.')))
											{	
												if(this_paper[j] == '.')
												{
													flag = 1;
												}
												else if(flag == 0)
												{	
													temp.w *= 10;
													temp.w += (this_paper[j] - '0');
												}
												else if(flag >= 1)
												{
													temp.w += ((this_paper[j] - '0') / pow(10, flag));
													flag++;
												}
												j++;
											}
										}
									}while((j < this_paper.size()) && (this_paper[j] != '}'));
									paper[i].fos.push_back(temp);
								}while((j < this_paper.size()) && (this_paper[j + 1] != ']'));
								break;

					case 7 :	do
								{
									string temp1 = get_next_word(this_paper, &j);
									paper[i].references.push_back(temp1);
								}while((j < this_paper.size()) && (this_paper[j] != ']'));
								break;

					case 8 :	j = j + 2;
								paper[i].n_citation = 0;
								while((j < this_paper.size()) && (this_paper[j] >= '0') && (this_paper[j] <= '9'))
								{
									paper[i].n_citation *= 10;
									paper[i].n_citation += (this_paper[j] - '0');
									j++;
								}
								break;

					case 9 :	paper[i].page_start = get_next_word(this_paper, &j);
								break;

					case 10 :	paper[i].page_end = get_next_word(this_paper, &j);
								break;

					case 11 :	paper[i].doc_type = get_next_word(this_paper, &j);
								break;

					case 12 :	paper[i].lang = get_next_word(this_paper, &j);
								break;

					case 13 :	paper[i].publisher = get_next_word(this_paper, &j);
								break;

					case 14 :	paper[i].volume = get_next_word(this_paper, &j);
								break;

					case 15 :	paper[i].issue = get_next_word(this_paper, &j);
								break;

					case 16 :	paper[i].issn = get_next_word(this_paper, &j);
								break;

					case 17 :	paper[i].isbn = get_next_word(this_paper, &j);
								break;

					case 18 :	paper[i].doi = get_next_word(this_paper, &j);
								break;

					case 19 :	paper[i].pdf = get_next_word(this_paper, &j);
								break;

					case 20 :	do
								{
									string temp1 = get_next_word(this_paper, &j);
									paper[i].url.push_back(temp1);
								}while((j < this_paper.size()) && (this_paper[j] != ']'));
								break;

					case 21 :	paper[i].abstract = get_next_word(this_paper, &j);
								break;

					case 22 :	get_next_word(this_paper, &j);
								j = j + 2;
								paper[i].indexed_abstract.IndexLength = 0;
								while((j < this_paper.size()) && (this_paper[j] >= '0') && (this_paper[j] <= '9'))
								{
									paper[i].indexed_abstract.IndexLength *= 10;
									paper[i].indexed_abstract.IndexLength += (this_paper[j] - '0');
									j++;
								}
								get_next_word(this_paper, &j);
								do
								{
									Word_index temp;
									temp.word = get_next_word(this_paper, &j);
									j = j + 3;
									string temp1;
									do
									{
										if(this_paper[j] == ',')
										{
											temp.index.push_back(temp1);
											temp1 = "";
											j = j + 1;
										}
										else
										{
											temp1.push_back(this_paper[j]);
										}
										j = j + 1;
									}while((j < this_paper.size()) && (this_paper[j] != ']'));
									temp.index.push_back(temp1);
									paper[i].indexed_abstract.InvertedIndex.push_back(temp);
								}while((j < this_paper.size()) && (this_paper[j + 1] != '}'));
								break;

					default :
								break;
				}
			}
		}
	}
}

void Collection :: map_attributes_to_integer()
{
	attributes.insert(pair<string, int>("id" , 0));
	attributes.insert(pair<string, int>("title", 1));
	attributes.insert(pair<string, int>("authors", 2));
	attributes.insert(pair<string, int>("venue", 3));
	attributes.insert(pair<string, int>("year", 4));
	attributes.insert(pair<string, int>("keywords", 5));
	attributes.insert(pair<string, int>("fos", 6));
	attributes.insert(pair<string, int>("references", 7));
	attributes.insert(pair<string, int>("n_citation", 8));
	attributes.insert(pair<string, int>("page_start", 9));
	attributes.insert(pair<string, int>("page_end", 10));
	attributes.insert(pair<string, int>("doc_type", 11));
	attributes.insert(pair<string, int>("lang", 12));
	attributes.insert(pair<string, int>("publisher", 13));
	attributes.insert(pair<string, int>("volume", 14));
	attributes.insert(pair<string, int>("issue", 15));
	attributes.insert(pair<string, int>("issn", 16));
	attributes.insert(pair<string, int>("isbn", 17));
	attributes.insert(pair<string, int>("doi", 18));
	attributes.insert(pair<string, int>("pdf", 19));
	attributes.insert(pair<string, int>("url", 20));
	attributes.insert(pair<string, int>("abstract", 21));
	attributes.insert(pair<string, int>("indexed_abstract", 22));
}