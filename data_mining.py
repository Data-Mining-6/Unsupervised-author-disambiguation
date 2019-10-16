data_file_name = 'data_set_aminar_dblp.v11/dblp_papers_v11.txt'
#data_file_name = 'data_set_aminar_dblp.v11/sample_of_dblp_papers_v11.txt'
no_of_sample = 100000

def get_next_word(this_paper):
	global j
	this_word = ''
	while j < len(this_paper) and this_paper[j] != '"':
		j = j + 1
	j = j + 1
	while j < len(this_paper) and this_paper[j] != '"':
		this_word = this_word + this_paper[j]
		j = j + 1
	j = j + 1
	return this_word

class Authors:
	def __init__(self):
		self.name = ''
		self.identity = ''
		self.org = ''

class Venue:
	def __init__(self):
		self.identity = ''
		self.raw = ''

class Fos:
	def __init__(self):
		self.name = ''
		self.w = 0.0

class Indexed_abstract:
	def __init__(self):
		self.IndexLength = 0
		self.InvertedIndex = []

class Word_index:
	def __init__(self):
		self.word = ''
		self.index = []

class Paper:
	def __init__(self):
		self.identity = ''
		self.title = ''
		self.authors = []
		self.venue = Venue()
		self.year = 0
		self.keywords = []
		self.fos = []
		self.references = []
		self.n_citation = 0
		self.page_start = ''
		self.page_end = ''
		self.doc_type = ''
		self.lang = ''
		self.publisher = ''
		self.volume = ''
		self.issue = ''
		self.issn = ''
		self.isbn = ''
		self.doi = ''
		self.pdf = ''
		self.url = []
		self.abstract = ''
		self.indexed_abstract = Indexed_abstract()

class Collection:
	def __init__(self):
		self.collection_size = no_of_sample
		self.paper = []
		self.attributes = {}

	def print_data(self):
		for i in self.paper:
			print('identity : ' + i.identity)
			print('title : ' + i.title)
			print('authors :')
			for j in i.authors:
				print('\tname : ' + j.name + '\tidentity : ' + j.identity + '\torg : ' + j.org)
			print('keywords :')
			for j in i.keywords:
				print('\t' + j)
			print('fos :')
			for j in i.fos:
				print('\tname : ' + j.name + '\tw : ' + str(j.w))
			print('references :')
			for j in i.references:
				print('\t' + j)
			print('venue :')
			print('\traw : ' + i.venue.raw + '\tidentity : ' + i.venue.identity)
			print('year : ' + str(i.year))
			print('n_citation : ' + str(i.n_citation))
			print('page_start : ' + i.page_start)
			print('page_end : ' + i.page_end)
			print('doc_type : ' + i.doc_type)
			print('lang : ' + i.lang)
			print('publisher : ' + i.publisher)
			print('volume : ' + i.volume)
			print('issue : ' + i.issue)
			print('issn : ' + i.issn)
			print('isbn : ' + i.isbn)
			print('doi : ' + i.doi)
			print('pdf : ' + i.pdf)
			print('url :')
			for j in i.url:
				print('\t' + j)
			print('indexed_abstract :')
			print('\tIndexLength : ' + str(i.indexed_abstract.IndexLength))
			print('\tInvertedIndex : ')
			for j in i.indexed_abstract.InvertedIndex:
				print('\t\tword : ' + j.word, end = '')
				print('\t\tIndex : ', end = '')
				for k in j.index:
					print(str(k), end = ',')
				print()
			print('\n')

	def read_data(self):
		global j
		input_file = open(data_file_name, "r")
		for i in range(0, self.collection_size):
			this_paper = input_file.readline()
			#print(i)
			#print(this_paper + '\n')
			paper = Paper()
			j = 0;
			if(this_paper == ''):
				self.collection_size = i;
				break
			while j < len(this_paper):
				this_word = get_next_word(this_paper)
				if this_word in self.attributes:
					key = self.attributes[this_word]
					if(key == 0):
						paper.identity = get_next_word(this_paper)
					elif(key == 1):
						paper.title = get_next_word(this_paper)
					elif(key == 2):
						while j < len(this_paper) and this_paper[j + 1] != ']':
							temp = Authors()
							j = j + 1
							while j < len(this_paper) and this_paper[j] != '}':
								temp1 = get_next_word(this_paper)
								if(temp1 == 'name'):
									temp.name = get_next_word(this_paper)
								elif(temp1 == 'id'):
									temp.identity = get_next_word(this_paper)
								elif(temp1 == 'org'):
									temp.org = get_next_word(this_paper)
							paper.authors.append(temp)
					elif(key == 3):
						while j < len(this_paper) and this_paper[j] != '}':
							temp = get_next_word(this_paper)
							if(temp == 'id'):
								paper.venue.identity = get_next_word(this_paper)
							elif(temp == 'raw'):
								paper.venue.raw = get_next_word(this_paper)
					elif(key == 4):
						j = j + 2
						temp = ''
						while j < len(this_paper) and this_paper[j] >= '0' and this_paper[j] <= '9':
							temp = temp + this_paper[j]
							j = j + 1
						paper.year = int(temp)
					elif(key == 5):
						while j < len(this_paper) and this_paper[j] != ']':
							paper.keywords.append(get_next_word(this_paper))
					elif(key == 6):
						while j < len(this_paper) and this_paper[j + 1] != ']':
							temp = Fos()
							j = j + 1
							while j < len(this_paper) and this_paper[j] != '}':
								temp1 = get_next_word(this_paper)
								if(temp1 == 'name'):
									temp.name = get_next_word(this_paper)
								elif(temp1 == 'w'):
									j = j + 2
									temp2 = ''
									while j < len(this_paper) and ((this_paper[j] >= '0' and this_paper[j] <= '9') or this_paper[j] == '.'):
										temp2 = temp2 + this_paper[j]
										j = j + 1
									temp.w = float(temp2)
							paper.fos.append(temp)
					elif(key == 7):
						while j < len(this_paper) and this_paper[j] != ']':
							paper.references.append(get_next_word(this_paper))
					elif(key == 8):
						j = j + 2
						temp = ''
						while j < len(this_paper) and this_paper[j] >= '0' and this_paper[j] <= '9':
							temp = temp + this_paper[j]
							j = j + 1
						paper.n_citation = int(temp)
					elif(key == 9):
						paper.page_start = get_next_word(this_paper)
					elif(key == 10):
						paper.page_end = get_next_word(this_paper)
					elif(key == 11):
						paper.doc_type = get_next_word(this_paper)
					elif(key == 12):
						paper.lang = get_next_word(this_paper)
					elif(key == 13):
						paper.publisher = get_next_word(this_paper)
					elif(key == 14):
						paper.volume = get_next_word(this_paper)
					elif(key == 15):
						paper.issue = get_next_word(this_paper)
					elif(key == 16):
						paper.issn = get_next_word(this_paper)
					elif(key == 17):
						paper.isbn = get_next_word(this_paper)
					elif(key == 18):
						paper.doi = get_next_word(this_paper)
					elif(key == 19):
						paper.pdf = get_next_word(this_paper)
					elif(key == 20):
						while j < len(this_paper) and this_paper[j] != ']':
							paper.url.append(get_next_word(this_paper))
					elif(key == 21):
						paper.abstract = get_next_word(this_paper)
					elif(key == 22):
						get_next_word(this_paper)
						j = j + 2
						temp = ''
						while j < len(this_paper) and this_paper[j] >= '0' and this_paper[j] <= '9':
							temp = temp + this_paper[j]
							j = j + 1
						paper.indexed_abstract.IndexLength = int(temp)
						get_next_word(this_paper)
						while j < len(this_paper) and this_paper[j + 1] != '}':
							temp1 = Word_index()
							temp1.word = get_next_word(this_paper)
							j = j + 3
							temp2 = ''
							while j < len(this_paper) and this_paper[j] != ']':
								if(this_paper[j] == ','):
									temp1.index.append(temp2)
									temp2 = ''
									j = j + 1
								else:
									temp2 = temp2 + this_paper[j]
								j = j + 1
							temp1.index.append(temp2)
							paper.indexed_abstract.InvertedIndex.append(temp1)
			self.paper.append(paper)
		input_file.close()

	def map_attributes_to_interger(self):
		self.attributes['id'] = 0
		self.attributes['title'] = 1
		self.attributes['authors'] = 2
		self.attributes['venue'] = 3
		self.attributes['year'] = 4
		self.attributes['keywords'] = 5
		self.attributes['fos'] = 6
		self.attributes['references'] = 7
		self.attributes['n_citation'] = 8
		self.attributes['page_start'] = 9
		self.attributes['page_end'] = 10
		self.attributes['doc_type'] = 11
		self.attributes['lang'] = 12
		self.attributes['publisher'] = 13
		self.attributes['volume'] = 14
		self.attributes['issue'] = 15
		self.attributes['issn'] = 16
		self.attributes['isbn'] = 17
		self.attributes['doi'] = 18
		self.attributes['pdf'] = 19
		self.attributes['url'] = 20
		self.attributes['abstract'] = 21
		self.attributes['indexed_abstract'] = 22

collection = Collection()
collection.map_attributes_to_interger()
collection.read_data()
#collection.print_data()