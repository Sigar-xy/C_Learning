#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

struct node {
	char data;
	node *lchild, *rchild;
};

void preOrder(node *root) {
	if(root == NULL) {
		return ;
	}
	printf("%c ", root->data);
	preOrder(root->lchild);
	preOrder(root->rchild);
}
void midOrder(node *root) {
	if(root == NULL) {
		return ;
	}
	midOrder(root->lchild);
	printf("%c ", root->data);
	midOrder(root->rchild);
}

void postOrder(node *root) {
	if(root == NULL) {
		return ;
	}
	postOrder(root->lchild);
	postOrder(root->rchild);
	printf("%c ", root->data);
}

void levelOrder(node *root) {
	queue<node*> q;
	q.push(root);
	while(!q.empty()) {
		node *head = q.front();
		q.pop();
		printf("%c ", head->data);
		if(head->lchild != NULL) {
			q.push(head->lchild);
		}
		if(head->rchild != NULL) {
			q.push(head->rchild);
		}
	}
}

//��������������������
node* create_pre_mid(int len, char *pre, char *mid) {
	if(len == 0) {
		return NULL;
	}
	node *root = new node;
	root->data = pre[0];
	
	int k;
	for(k = 0; k < len; k++ ) {
		if(pre[0] == mid[k]) {
			break;
		}
	}
	//ÿ�δ���ȥ���������ָ�룬 ����ÿ�ν������Ǵ��±�0��ʼ 
	root->lchild = create_pre_mid(k, pre + 1, mid);
	root->rchild = create_pre_mid(len - k - 1, pre + k + 1, mid + k + 1);
	
	return root;
} 
//����������������齨��
node* create_post_mid(int len, char *post, char *mid) {
	if(len == 0) return NULL;
	
	node *root = new node;
	root->data = post[len - 1];
	int k;
	for(k = 0; k < len; k++ ) {
		if(post[len - 1] == mid[k]) {
			break;
		}
	}
	
	root->lchild = create_post_mid(k, post, mid);
	root->rchild = create_post_mid(len - k - 1, post + k, mid + k + 1);
	
	return root;
}
//����(��)������������鹹���� 
node* create_level_mid(int len, char *level, char *mid) {
	if(len == 0) {
		return NULL;
	}
	char left[20], right[20];//�������µĲ������������ 
	int lcount = 0, rcount = 0;//������������������������ĸ��� 
	
	node *root = new node;
	root->data = level[0];
	int k; //����ȷ��ͷ�ڵ��� ��������е��±�
	for(k = 0; k < len; k++) {
		if(level[0] == mid[k]) {
			break;
		}
	} 
	
	for(int i = 0; i < len; i++) {
		for(int l = 0; l < k; l++) { //ȡ�����������ߵ����� 
			if(level[i] == mid[l]) {
				left[lcount++] = level[i];
			}
		}
		for(int r = k + 1; r < len; r++) {
			if(level[i] == mid[r]) {
				right[rcount++] = level[i];
			}
		}
	}
	
	root->lchild = create_level_mid(lcount, left, mid);
	root->rchild = create_level_mid(rcount, right, mid + k + 1);
	
	return root; 
}

int main() {
	
	char mid[10] = "DBFEAGCHI";
	char level[10] = "ABCDEGHFI";
	char pre[10] = "ABDEFCGHI";
	char post[10] = "DFEBGIHCA";
	int len = strlen(mid);
	
	node *root = new node;
	//root = create_level_mid(len, level, mid);
	//root = create_pre_mid(len, pre, mid); 
	root = create_post_mid(len, post, mid);
	
	preOrder(root);
	printf("\n");
	
	midOrder(root);
	printf("\n");
	
	postOrder(root);
	printf("\n");
	
	levelOrder(root);
	return 0;
}
