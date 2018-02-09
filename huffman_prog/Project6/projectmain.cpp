#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct CharFrequency {
	char character;
	int frequency;
	struct CharFrequency *next;
} CharFrequency;

typedef struct Tree {
	Tree* left;
	Tree* right;
	Tree* parent;
	struct CharFrequency data;
}Tree;
typedef Tree * pTree;

typedef struct MinHeap
{
	int elementCount;
	pTree * pData;
}MinHeap;

typedef CharFrequency * pCharFrequency;
typedef MinHeap * pMinHeap;

typedef struct queuenode{
	pTree data;
	struct queuenode *link;
}queuenode;
typedef struct queuetype{
	queuenode *front, *rear;
}queuetype;
void init_queue(queuetype *q){
	q->front = q->rear = NULL;
}
int is_empty_queue(queuetype *q){
	return (q->front == NULL);
}
void enqueue(queuetype *q, pTree data)
{
	queuenode *temp = (queuenode*)malloc(sizeof(queuenode));

	temp->data = data;
	temp->link = NULL;
	if (is_empty_queue(q))
	{
		q->front = temp;
		q->rear = temp;
	}
	else
	{
		q->rear->link = temp;
		q->rear = temp;
	}
}
pTree dequeue(queuetype *q)
{
	queuenode *temp = q->front;
	pTree ptr;

	ptr = temp->data;
	q->front = q->front->link;
	if (q->front == NULL)
	{
		q->rear = NULL;
	}
	free(temp);
	return ptr;
}

typedef struct stacknode{
	pTree data;
	stacknode* link;
}stacknode;
typedef struct stacktype{
	stacknode *top;
}stacktype;
void init_stack(stacktype *s)
{
	s->top = NULL;
}
int is_empty_stack(stacktype *s)
{
	return (s->top == NULL);
}
void push(stacktype *s, pTree data)
{
	stacknode *temp = (stacknode*)malloc(sizeof(stacknode));
	temp->data = data;
	temp->link = s->top;
	s->top = temp;
}
pTree pop(stacktype *s)
{
	stacknode *temp = s->top;
	pTree data = temp->data;
	s->top = s->top->link;
	free(temp);
	return data;
}

pTree findlastnode(pTree ptr)
{
	queuetype q;
	stacktype s;
	pTree t, forward;
	init_queue(&q);
	init_stack(&s);
	enqueue(&q, ptr);
	while (!is_empty_queue(&q))
	{
		t = dequeue(&q);
		if (t->left)
			enqueue(&q, t->left);
		if (t->right)
			enqueue(&q, t->right);
		if ((t->left) && (t->right))
		{
			push(&s, t);
		}
		else if (!(t->left))    //왼쪽노드도 없는 경우, 상위 오른쪽노드가 마지막노드
		{
			if (is_empty_stack(&s))
			{
				return t;
			}
			forward = pop(&s);
			t = forward->right;
			forward->right = NULL;
			return t;
		}
		else //왼쪽노드는 있고 오른쪽노드가 없는 경우 ->왼쪽이 마지막이므로
		{
			forward = t;
			t = forward->left;
			forward->left = NULL;
			return t;
		}
	}
}
void heapsort(pTree phead)
{
	CharFrequency temp;
	if (!(phead->right) && !(phead->left))
		return;

	if (!(phead->right))
	{
		if ((phead->data.frequency) > (phead->left->data.frequency))
		{
			temp = phead->data;
			phead->data = phead->left->data;
			phead->left->data = temp;
			return;
		}
	}
	else
	{
		if ((phead->left->data.frequency < phead->right->data.frequency))
		{
			if (phead->left->data.frequency < phead->data.frequency)
			{
				temp = phead->left->data;
				phead->left->data = phead->data;
				phead->data = temp;
				heapsort(phead->left);
			}
		}
		else
		{
			if (phead->right->data.frequency < phead->data.frequency)
			{
				temp = phead->right->data;
				phead->right->data = phead->data;
				phead->data = temp;
				heapsort(phead->right);
			}
		}
	}
}
void levelorder(pTree ptr, CharFrequency data)
{
	queuetype q;
	pTree t;
	CharFrequency temp;
	init_queue(&q);
	if (!ptr)
	{
		ptr->left = NULL;
		ptr->right = NULL;
		ptr->parent = NULL;
		ptr->data = data;
	}
	enqueue(&q, ptr);
	while (!is_empty_queue(&q))
	{
		t = dequeue(&q);
		if (t->left)
			enqueue(&q, t->left);
		if (t->right)
			enqueue(&q, t->right);
		if (!(t->left) || !(t->right))
		{
			if (!(t->left))
			{
				pTree newtree = (pTree)malloc(sizeof(Tree));
				t->left = newtree;
				newtree->data = data;
				newtree->left = NULL;
				newtree->right = NULL;
				newtree->parent = t;
				while (newtree->parent != NULL)
				{
					if (newtree->data.frequency<newtree->parent->data.frequency)
					{
						temp = newtree->data;
						newtree->data = newtree->parent->data;
						newtree->parent->data = temp;
					}
					newtree = newtree->parent;
				}
				return;
			}
			else if (!(t->right))
			{
				pTree newtree = (pTree)malloc(sizeof(Tree));
				t->right = newtree;
				newtree->data = data;
				newtree->left = NULL;
				newtree->right = NULL;
				newtree->parent = t;
				while (newtree->parent != NULL)
				{
					if (newtree->data.frequency<newtree->parent->data.frequency)
					{
						temp = newtree->data;
						newtree->data = newtree->parent->data;
						newtree->parent->data = temp;
					}
					newtree = newtree->parent;
				}
				return;
			}
		}
	}
}
void inserttree(pTree *phead, CharFrequency data){
	pTree p, t;
	pTree n = (pTree)malloc(sizeof(Tree));
	t = *phead;
	p = NULL;

	if (*phead == NULL)
	{
		*phead = n;
		n->data = data;
		n->left = n->right = NULL;
		n->parent = NULL;
	}
	else
	{
		levelorder(*phead, data);
	}
}
pTree deletetree(pTree *phead)
{
	pTree delete_ = (pTree)malloc(sizeof(Tree));
	delete_ = (*phead);
	pTree root;
	root = findlastnode(*phead);
	root->left = (*phead)->left;
	root->right = (*phead)->right;
	*phead = root;
	heapsort(*phead);
	delete_->left = NULL;
	delete_->right = NULL;
	delete_->parent = NULL;
	return delete_;
}

//========================================================================//
//Alphabet//
pCharFrequency initList()
{
	pCharFrequency listhead = (pCharFrequency)malloc(sizeof(CharFrequency));
	listhead = NULL;
	return listhead;
}
void addnode(pCharFrequency *listhead, char ch)
{
	pCharFrequency s = NULL;
	s = *listhead;
	while (s != NULL)
	{
		if (s->character == ch)
		{
			s->frequency += 1;
			return;
		}
		if (s->next == NULL)
			break;
		s = s->next;
	}

	if (*listhead == NULL)
	{
		pCharFrequency listnode = (pCharFrequency)malloc(sizeof(CharFrequency));
		(*listhead) = listnode;
		listnode->next = NULL;
		listnode->character = ch;
		listnode->frequency = 1;
	}
	else
	{
		pCharFrequency listnode = (pCharFrequency)malloc(sizeof(CharFrequency));
		s->next = listnode;
		listnode->character = ch;
		listnode->next = NULL;
		listnode->frequency = 1;
	}
}

pCharFrequency FindContainNode(pCharFrequency pHead, char ch)
{
	pCharFrequency s = pHead;
	if (pHead == NULL)
	{
		return NULL;
	}
	else
	{
		while (s != NULL)
		{
			if (s->character == ch)
				return s;
			s = s->next;
		}
		return NULL;
	}
}
void printlistnode(pCharFrequency *listhead)
{
	while (*listhead)
	{
		printf("%c : %d\n", (*listhead)->character, (*listhead)->frequency);
		(*listhead) = (*listhead)->next;
	}
}


//========================================================================//
//Priority Queue
pMinHeap createMinHeap()
{
	pMinHeap pHeap = (pMinHeap)malloc(sizeof(MinHeap));
	pHeap->pData = (pTree*)malloc(26*sizeof(pTree));
	pHeap->elementCount = 0;
	return pHeap;
}
void insertMinHeap(pMinHeap pHeap, pTree pHead_Tree)
{
	int i;
	pTree temp;
	pHeap->elementCount++;
	i = pHeap->elementCount;
	pHeap->pData[i]=pHead_Tree;
	

	while (1)
	{
		if (i == 1)
			return;
		else
		{
			if (pHeap->pData[i]->data.frequency < pHeap->pData[(int)i / 2]->data.frequency)
			{
				temp = pHeap->pData[i];
				pHeap->pData[i] = pHeap->pData[(int)i / 2];
				pHeap->pData[(int)i / 2] = temp;
				i = (int)i / 2;
			}
			else
				return;
		}
	}
	
}
pTree deleteMinHeap(pMinHeap pHeap) {
	
	int element;
	int i;
	pTree temp;
	if (pHeap == NULL)
		return NULL;
	else
	{
		element = pHeap->elementCount;
		pTree del = (pTree)malloc(sizeof(Tree));
		del = pHeap->pData[1];
		pHeap->pData[1] = pHeap->pData[element];
		pHeap->pData[element] = NULL;
		pHeap->elementCount--;
		i = 1;

		while (2*i <= pHeap->elementCount)
		{
			if (pHeap->pData[2 * i + 1] == NULL)
			{
				if (pHeap->pData[i]->data.frequency>pHeap->pData[2 * i]->data.frequency)
				{
					temp = pHeap->pData[i];
					pHeap->pData[i] = pHeap->pData[2 * i];
					pHeap->pData[2 * i] = temp;
					i = i * 2;
				}
				else
					break;
			}
			else if (pHeap->pData[2 * i]->data.frequency < pHeap->pData[2 * i + 1]->data.frequency)
			{
				if (pHeap->pData[i]->data.frequency>pHeap->pData[2 * i]->data.frequency)
				{
					temp = pHeap->pData[i];
					pHeap->pData[i] = pHeap->pData[2 * i];
					pHeap->pData[2 * i] = temp;
					i = i * 2;
				}
				else
					break;
			}
			else
			{
				if (pHeap->pData[i]->data.frequency > pHeap->pData[2 * i + 1]->data.frequency)
				{
					temp = pHeap->pData[i];
					pHeap->pData[i] = pHeap->pData[2 * i + 1];
					pHeap->pData[2 * i + 1] = temp;
					i = i * 2 + 1;
				}
				else
					break;
			}
			
		}
		return del;
	}
	
}

//========================================================================//
//Huffman Tree
pTree createtree(){
	pTree phead = (pTree)malloc(sizeof(Tree));
	phead = NULL;
	return phead;
}
pTree MakeTree(pTree left, pTree right)
{
	pTree root = (pTree)malloc(sizeof(Tree));
	if (root == NULL)
	{
		fprintf(stderr, "메모리에러\n");
		exit(1);
	}
	root->left = left;
	root->right = right;
	root->data.character = NULL;
	root->data.frequency = left->data.frequency + right->data.frequency;
	return root;
}

void createHuffmanTree(pMinHeap pHead_MinHeap)
{
	pTree left, right,root;
	root = (pTree)malloc(sizeof(pTree));

	while (pHead_MinHeap->elementCount != 1)
	{
		left = deleteMinHeap(pHead_MinHeap);
		right = deleteMinHeap(pHead_MinHeap);

		root = MakeTree(left, right);
		insertMinHeap(pHead_MinHeap, root);
	}
	
}
//HuffmanTree doesn't have only one child.



void PrintTree(pTree tree, int i, char *pCode)
{
	if (tree == NULL)
		return;
	else
	{
		i++;
		pCode[i] = '0';
		PrintTree(tree->left, i, pCode);
		pCode[i] = '1';
		PrintTree(tree->right, i, pCode);

		pCode[i] = '\0';

		if (!(tree->left)&&!(tree->right))
			printf("Character:%c\t Frequency:%d\t Bin:%s\n", tree->data.character, tree->data.frequency, pCode);
	}
}


int main()
	{

		int i, k = 0, j = 0, l = 0;
		int count = 0;
		char temp[30];
		char buf[500];
		char deli[76] = { 0 };
		char bin[20];
		char *ptr = NULL;
		pTree phead = createtree();
		pTree huff = createtree();
		pCharFrequency listhead = initList();
		pMinHeap pminheap = createMinHeap();
		pCharFrequency h;
		//File Read
		FILE *f;
		if (fopen_s(&f, "dataset.txt", "r"))
		{
			printf("File can't open!");
			return -1;
		}
		for (i = 0; i < 128; i++) //아스키코드 영문제외,
		{
			if ((i > 0 && i<65) || (i>90 && i<97) || (i >122 && i <= 127))
				deli[k++] = i;
		}
		while (!feof(f)) {
			fgets(buf, sizeof(buf), f);
			ptr = strtok(buf, deli);
			while (ptr != NULL)
			{
				strcpy(temp, ptr);
				i = strlen(temp);
				for (k = 0; k < i; k++)
				{
					if (temp[k] < 97)
						temp[k] += 32;
					addnode(&listhead, temp[k]);
					l++;
				}
				ptr = strtok(NULL, deli);
			}
		}
		fclose(f);
		h = listhead;
		
		while (h != NULL)
		{
			inserttree(&phead, *h);
			h = h->next;
			count++;
		}
		for (i = 0; i < count;i++)
		{
			insertMinHeap(pminheap, deletetree(&phead));
		}
		createHuffmanTree(pminheap);

		PrintTree(pminheap->pData[1], -1, bin);
	
	}

