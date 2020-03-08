# include <stdio.h>
# include <stdlib.h>

# define bool char		//��������
# define true 1
# define false 0
# define ElementType int
# define MAX_SAQ_SIZE 2147483647



//______________________________________________________________

/**
	�ṹ�嶨��
**/
 
typedef struct X{		// ������
	ElementType data;	// ������ 
	struct X *left;		// ������ 
	struct X *right;	// ������ 
}BinTree;				


typedef struct Y{		// �����ڽڵ�
	struct Y *fore;		// ǰ�� 
	struct Y *next;		// ��� 
	BinTree *self;		// ����ڵ� 
}SaQNode;  				


typedef struct Z{		// ˫������, �䵱�������Ķ��к�ջ������ 
	SaQNode *head;		// ����ͷ 
	SaQNode *tail;		// ����β 
	int length;			// �����д��� 
	int maxsize;		// ���� 
}SAQ;					
 

//______________________________________________________________

/**
	��������غ������� 
**/
 
void recursivePreorderTraversal(BinTree* root);
void recursiveMiddleorderTraversal(BinTree* root);
void recursivePostorderTraversal(BinTree* root);
void noRecursivePreorderTraversal(BinTree* root);
void noRecursiveMiddleorderTraversal(BinTree* root);
void noRecursivePostorderTraversal(BinTree* root);
BinTree *createNewNode(ElementType data);



/**
	˫��������غ�������
**/

bool pushSAQ(SAQ *saq, BinTree *btnode);
bool showSaQData(SAQ *saq);
SAQ *createSAQ(int maxsize);
SaQNode *createSaQNode(BinTree *btNode);
BinTree *stackPop(SAQ *saq);
BinTree *queuePop(SAQ *saq); 

//_______________________________________________________________

/**
	������ 
**/

int main(){
	int i;
	SAQ *stack, *que;
	BinTree *root, *bt1, *bt2, *bt3, *bt4, *bt5;
	BinTree *bintree[5];
	root = createNewNode(0);
	bt1 = createNewNode(1);
	bt2 = createNewNode(2);
	bt3 = createNewNode(3);
	bt4 = createNewNode(4);
	bt5 = createNewNode(5);
	root->left = bt1;
	root->right = bt2;
	bt1->left = bt3;
	bt1->right = bt4;
	bt2->left = bt5;
	printf("�ݹ��������: ");
	recursivePreorderTraversal(root);
	printf("\n");
	printf("�ǵݹ��������: ");
	noRecursivePreorderTraversal(root);
	printf("\n");
	printf("�ݹ��������: ");
	recursiveMiddleorderTraversal(root);
	printf("\n");
	printf("�ǵݹ��������: ");
	noRecursiveMiddleorderTraversal(root);
	printf("\n");
	printf("�ݹ�������: ");
	recursivePostorderTraversal(root);
	printf("\n");
	printf("�ǵݹ�������: ");
	noRecursivePostorderTraversal(root);
//	stack = createSAQ(10);
//	showSaQData(stack);
//	pushSAQ(stack, root);
//	stackPop(stack);
//	pushSAQ(stack, bt1);
//	pushSAQ(stack, bt1);
//	pushSAQ(stack, bt2);
//	pushSAQ(stack, bt3);
//	pushSAQ(stack, bt4);
//	pushSAQ(stack, bt5);
//	showSaQData(stack);
//	stackPop(stack);
//	queuePop(stack);
//	showSaQData(stack);
	return 0;
}



//_______________________________________________________________

/**
	��������غ�������
**/
 
BinTree *createNewNode(ElementType data){			// �����������ڵ� 
	BinTree *node;
	node = (BinTree*) malloc(sizeof(BinTree));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}


void recursivePreorderTraversal(BinTree* root){		// �ݹ�������������� 
	BinTree *tag;
	tag = root;
	printf("%d ", tag->data);
	if(tag->left != NULL)
		recursivePreorderTraversal(tag->left);
	if(tag->right != NULL)
		recursivePreorderTraversal(tag->right);
}


void recursiveMiddleorderTraversal(BinTree* root){	// �ݹ�������������� 
	BinTree *tag;
	tag = root;
	if(tag->left != NULL)
		recursiveMiddleorderTraversal(tag->left);
	printf("%d ", tag->data);
	if(tag->right != NULL)
		recursiveMiddleorderTraversal(tag->right);
}


void recursivePostorderTraversal(BinTree* root){	// �ݹ������������� 
	BinTree *tag;
	tag = root;
	if(tag->left != NULL)
		recursivePostorderTraversal(tag->left);
	if(tag->right != NULL)
		recursivePostorderTraversal(tag->right);
	printf("%d ", tag->data);
}


void noRecursivePreorderTraversal(BinTree* root){	// �ǵݹ�������������� 
	SAQ *stack;
	BinTree *p;
	stack = createSAQ(-1);
	p = root;
	if(!root){
		printf("��Ϊ��\n");
		return;
	}
	pushSAQ(stack, p);
	while(stack->length){
		p = stackPop(stack);
		printf("%d ", p->data);
		if(p->right)
			pushSAQ(stack, p->right);
		if(p->left)
			pushSAQ(stack, p->left);
	}
}


void noRecursiveMiddleorderTraversal(BinTree* root){// �ǵݹ�������������� 
	SAQ *stack;
	BinTree *p;
	stack = createSAQ(-1);
	p = root;
	if(!root){
		printf("��Ϊ��\n");
		return;
	}
	while(stack->length != 0 || p){
		while(p){
			pushSAQ(stack, p);
			p = p->left;
		}
		if(stack->length != 0){
			p = stack->tail->self;
			stackPop(stack);
  			printf("%d ", p->data);
  			p = p->right;
		}
	}
}


void noRecursivePostorderTraversal(BinTree* root){	// �ǵݹ������������� 
	SAQ *stack;
	BinTree *p;
	stack = createSAQ(-1);
	p = root;
	if(!root){
		printf("��Ϊ��\n");
		return;
	}
	pushSAQ(stack, root);
	pushSAQ(stack, root);
	while(stack->length){
		p = stackPop(stack);
		if(stack->length && p == stack->tail->self){
			if(p->right){
				pushSAQ(stack, p->right);
				pushSAQ(stack, p->right);
			}
			if(p->left){
				pushSAQ(stack, p->left);
				pushSAQ(stack, p->left);
			}
		}else{
			printf("%d ", p->data);
		}
	}
}



/**
	˫��������غ�������
**/ 

SAQ *createSAQ(int maxsize){						// �������� 
	SAQ *saq;
	SaQNode *head;
	saq = (SAQ*) malloc(sizeof(SAQ));
	head = (SaQNode*) malloc(sizeof(SaQNode));
	head->fore = NULL;
	head->next = NULL;
	head->self = NULL;
	saq->head = NULL;
	saq->tail = saq->head;
	saq->length = 0;
	if(maxsize < 0)
		saq->maxsize = MAX_SAQ_SIZE;
	else
		saq->maxsize = maxsize;
	return saq;
}


SaQNode *createSaQNode(BinTree *btNode){			// ���������� 
	SaQNode *saqnode;
	saqnode = (SaQNode*) malloc(sizeof(SaQNode));
	saqnode->fore = NULL;
	saqnode->next = NULL;
	saqnode->self = btNode;
	return saqnode;
}


bool showSaQData(SAQ *saq){							// ��ʾ���������� 
	SaQNode *p;
	p = saq->head;
	if(saq->length == 0){
		printf("SAQΪ��\n");
		return false;
	}
	printf("head->");
	while(p){
		printf(" %d ", p->self->data);
		if(p->next)
			printf("<->");
		p = p->next;
	}
	printf("<-tail\n");
	return true;
}


bool pushSAQ(SAQ *saq, BinTree *btnode){			// ����βpush���� 
	SaQNode *node;
	node = createSaQNode(btnode);
	if(saq->length == saq->maxsize){
		printf("SAQ����\n");
		return false;
	}else if(saq->length == 0){
		saq->head = node;
	}else{
		saq->tail->next = node;
		node->fore = saq->tail;
	}
	saq->tail = node;
	(saq->length) ++;
//	printf("push: ��ǰ����: %d\n", saq->length);
	return true;
}


BinTree *stackPop(SAQ *saq){						// ջpop���� 
	SaQNode *p;
	if(saq->length == 0){
		printf("SAQ��");
		return NULL;
	}else if(saq->length == 1){
		p = saq->tail;
		saq->head = NULL;
		saq->tail = NULL;
	}else{
		p = saq->tail;
		saq->tail = saq->tail->fore;
		p->fore = NULL;
		saq->tail->next = NULL;
	}
	(saq->length) --;
//	printf("stackpop: ��ǰ����%d\n", saq->length);
	return p->self;
}


BinTree *queuePop(SAQ *saq){						// ����pop���� 
	SaQNode *p;
	if(saq->length == 0){
		printf("SAQ��");
		return NULL;
	}else if(saq->length == 0){
		p = saq->head;
		saq->head = NULL;
		saq->tail = NULL;
	}else{
		p = saq->head;
		saq->head = saq->head->next;
		p->next = NULL;
		saq->head->fore = NULL;
	}
	(saq->length) --;
//	printf("stackpop: ��ǰ����%d\n", saq->length);
	return p->self;
}
//_______________________________________________________________

