# include <stdio.h>
# include <stdlib.h>
# include <time.h>


# define ElementType int
# define MAX_SIZE 101
# define MAX_NUM 101
# define MIN_NUM -1
# define bool char
# define true 1
# define false 0

# define TEST_NUM 20
# define TEST_MAX 99



typedef struct X{
	ElementType *data;				
	int length;
	int max_size;
	bool max_heap;
} Heap;


//______________________________________________________________________________


Heap *createHeapFromArray(ElementType *arr, int arr_size, int max_size, bool max_heap);
Heap *createHeap(int max_size, bool max_heap);
bool pushHeap(Heap *heap, ElementType elem);
ElementType popHeap(Heap *heap);
void arrayHeapSort(ElementType *arr, int arr_size, bool reserve);


//______________________________________________________________________________


int main(){
	int i, a[TEST_NUM];
	Heap *max, *min, *heap;
	max = createHeap(100, true);
	min = createHeap(100, false);
	srand((unsigned)time(NULL));
	printf("max: %d\n", max->data[0]);
	for(i=0; i<TEST_NUM; i++){
		a[i] = rand()%(TEST_MAX+1);
		a[i] = TEST_NUM-i;
		a[i] = i;
		pushHeap(max, a[i]);
		pushHeap(min, a[i]);
	}
	printf("\nԭ����: ");
	for(i=0; i<TEST_NUM; i++){
		printf("%d ", a[i]);
	}
	printf("\n�󶥶�: ");
	for(i=1; i<=max->length; i++){
		printf("%d ", max->data[i]);
	}
	printf("\nС����: ");
	for(i=1; i<=min->length; i++){
		printf("%d ", min->data[i]);
	}
	printf("\n�󶥶�pop: ");
	for(i=1; i<max->length;){
		printf("%d ", popHeap(max));
	}
	printf("\nС����pop: ");
	for(i=1; i<min->length;){
		printf("%d ", popHeap(min));
	}
	printf("\n");
	heap = createHeapFromArray(a, TEST_NUM, 0, true);
	printf("�����鴴��: ");
	for(i=1; i<=heap->length; i++){
		printf("%d ", heap->data[i]);
	}
	printf("\nheap pop: ");
	for(i=0; i<heap->length;){
		printf("%d ", popHeap(heap));
	}
	arrayHeapSort(a, TEST_NUM, false);
	printf("\n����������: ");
	for(i=0; i<TEST_NUM; i++){
		printf("%d ", a[i]);
	}
	printf("\nOK");
	return 0;
}


//______________________________________________________________________________


Heap *createHeap(int max_size, bool max_heap){
	Heap *heap;
	int i;
	heap = (Heap*) malloc(sizeof(Heap));
	heap->length = 0;
	heap->max_heap = max_heap;
	if(max_size>0)
		heap->max_size = max_size; 
	else
		heap->max_size = MAX_SIZE;
	heap->data = (ElementType*) malloc(heap->max_size*(sizeof(ElementType)));
	heap->length = 0;
	if(max_heap){
		heap->data[0] = MAX_NUM;
		for(i=1; i<heap->max_size; i++){
			heap->data[i] = MIN_NUM;
		}
	}
	else{
		heap->data[0] = MIN_NUM;
		for(i=1; i<heap->max_size; i++)
			heap->data[i] = MAX_NUM;
	}
	return heap;
}


Heap *createHeapFromArray(ElementType *arr, int arr_size, int max_size, bool max_heap){
	int i, tmp_i;
	Heap *heap;
	ElementType tmp;
	if(arr_size > max_size && max_size > 0){
		printf("��������С��Ԫ������\n");
		return NULL;
	}
	heap = createHeap(max_size, max_heap);
	for(i=0; i<arr_size; i++){
		heap->length ++;
		heap->data[i+1] = arr[i];
	}
	i = (heap->length) / 2;
	switch(max_heap){
		case true:{
			while(i){
				if(heap->data[i] >= heap->data[2*i] && heap->data[i] >= heap->data[2*i+1]){
					i --;
					continue;
				}else{
					tmp = heap->data[i];
					tmp_i = i;
					while(2*tmp_i <= heap->length){
						if(tmp > heap->data[2*tmp_i] && tmp > heap->data[2*tmp_i+1])
							break;
						else{
							if(heap->data[2*tmp_i] > heap->data[2*tmp_i+1]){
								heap->data[tmp_i] = heap->data[2*tmp_i];
								tmp_i = 2*tmp_i;
							}else{
								heap->data[tmp_i] = heap->data[2*tmp_i+1];
								tmp_i = 2*tmp_i+1;
							}
						}
					}
					heap->data[tmp_i] = tmp;
				}
				i --;
			}
			break;
		}
		case false:{
			while(i){
				if(heap->data[i] <= heap->data[2*i] && heap->data[i] <= heap->data[2*i+1]){
					i --;
					continue;
				}else{
					tmp = heap->data[i];
					tmp_i = i;
					while(2*tmp_i <= heap->length){
						if(tmp < heap->data[2*tmp_i] && tmp < heap->data[2*tmp_i+1])
							break;
						else{
							if(heap->data[2*tmp_i] < heap->data[2*tmp_i+1]){
								heap->data[tmp_i] = heap->data[2*tmp_i];
								tmp_i = 2*tmp_i;
							}else{
								heap->data[tmp_i] = heap->data[2*tmp_i+1];
								tmp_i = 2*tmp_i+1;
							}
						}
					}
					heap->data[tmp_i] = tmp;
				}
				i --;
			}
			break;
		}
	}
	return heap;
}


bool pushHeap(Heap *heap, ElementType elem){
	int i;
	switch(heap->max_heap){
		case true:{
			if(elem > heap->data[0]){
				printf("���ڴ󶥶����ֵ������ʧ�ܣ�\n");
				return false;
			}
			heap->length ++;
			i = heap->length;
			heap->data[i] = elem;
			while(i){
				if(elem > heap->data[i/2]){
					heap->data[i] = heap->data[i/2];
					i /= 2;
				}else{
					heap->data[i] = elem;
					break;
				}
			}
			return true;
		}
		case false:{
			if(elem < heap->data[0]){
				printf("С�ڴ󶥶����ֵ������ʧ�ܣ�\n");
				return false;
			}
			heap->length ++;
			i = heap->length;
			heap->data[i] = elem;
			while(i){
				if(elem < heap->data[i/2]){
					heap->data[i] = heap->data[i/2];
					i /= 2;
				}else{
					heap->data[i] = elem;
					break;
				}
			}
			return true;
		}
	}
}


ElementType popHeap(Heap *heap){
	int i;
	ElementType ret, tmp;
	if(heap->length == 0){
		printf("�ѿ�\n");
		return heap->data[0];
	}
	ret = heap->data[1];
	tmp = heap->data[heap->length];
	heap->length --;
	switch(heap->max_heap){
		case true:{
			heap->data[1] = heap->data[i];
			i = 1;
			while(2*i <= heap->length){
				if(tmp > heap->data[2*i] && tmp > heap->data[2*i+1])
					break;
				else{
					if(heap->data[2*i] > heap->data[2*i+1]){
						heap->data[i] = heap->data[2*i];
						i = 2*i;
					}else{
						heap->data[i] = heap->data[2*i+1];
						i = 2*i+1;
					}
				}
			}
			heap->data[i] = tmp;
			break;
		}
		case false:{
			heap->data[1] = heap->data[i];
			i = 1;
			while(2*i <= heap->length){
				if(tmp < heap->data[2*i] && tmp < heap->data[2*i+1])
					break;
				else{
					if(heap->data[2*i] < heap->data[2*i+1]){
						heap->data[i] = heap->data[2*i];
						i = 2*i;
					}else{
						heap->data[i] = heap->data[2*i+1];
						i = 2*i+1;
					}
				}
			}
			heap->data[i] = tmp;
			break;
		}
	}
	return ret;
}


void arrayHeapSort(ElementType *arr, int arr_size, bool reserve){// ԭ�ض����� 
	int i = arr_size / 2 - 1;	// i�Ǵӵ�һ���к��ӵĽ�㻹�� 
	int len, tmp_i;
	ElementType tmp;
	if(arr_size <= 1){
		printf("��������\n");
		return;
	}
	switch(reserve){	
		case false:{	// ����: ����󶥶� 
		/**
		   ��һ��: ԭ�ع���󶥶�
		   **/ 
			while(i+1){	// ���ѭ���Ǵӵ�һ���к��ӵĽ�㿪ʼ, ÿ��--, ����ǰ����������ɴ󶥶�, �����0�����һ�ν���ѭ������ 
				if(i*2+2 < arr_size){	// �����ǰ�ڵ����Һ��� (һ��������), ����Ԫ���ж� 
					tmp = arr[i];	// ���浱ǰ�ڵ�
					tmp_i = i;		// ����סiֵ 
					while(2*tmp_i+1 < arr_size){	// �ڲ�ѭ������ǰ����������ɴ󶥶�, �����ҵ���tmp_iΪiӦ���ڵ�λ��, ��ֹ����Ϊ��ǰ�ڵ�Ϊ��Ҷ�ڵ�
						if(2*tmp_i+2 < arr_size){	// ���Һ���, �����ж� 
							if(tmp >= arr[2*tmp_i+1] && tmp >= arr[2*tmp_i+2]){	// �����ǰ�ڵ���������ӽڵ���˵���ҵ�tmp_iӦ���ڵ�λ���� 
								break;
							}else{	// ����û���ҵ�, ��������Ѱ��, ���Һ����д�ڵ�һ�����ڵ�ǰ�ڵ� 
								if(arr[2*tmp_i+1] >= arr[2*tmp_i+2]){	// ��ڵ�� 
									arr[tmp_i] = arr[2*tmp_i+1];	// ��ڵ�Ų����
									tmp_i = 2*tmp_i+1;	// tmp_i�����ڵ� 
								}else{	// �ҽڵ��
									arr[tmp_i] = arr[2*tmp_i+2];	
									tmp_i = 2*tmp_i+2;
								}
							}
						}else{	// û�Һ���, ��ֻ���жϵ�ǰ�ڵ�����ڵ� 
							if(tmp < arr[2*tmp_i+1]){	// ��ǰ�ڵ�С����ڵ��򽻻�, �����ҵ� 
								arr[tmp_i] = arr[2*tmp_i+1];
								tmp_i = 2*tmp_i+1;
							}else{
								break;
							}
						}
					}
					// �����ڲ�ѭ���Ѿ��ҵ�tmp_iӦ����λ��, ���ҳ���Ӧ����λ��֮�������Ԫ�ض���������, ��������ֻ��Ҫ��tmp�ƹ�������
					arr[tmp_i] = tmp; 
				}else{	// �����ǰ�ڵ����Һ���, ���Ԫ���ж�, ��������һ��ΪҶ�ڵ�, ��ֻ���жϵ�ǰλ���������ӹ��ɵ����Ƿ�Ϊ�� 
					if(arr[i] < arr[2*i+1]){	// ˳�򲻶�, ���� 
						tmp = arr[i];
						arr[i] = arr[2*i+1];
						arr[2*i+1] = tmp;
					}else{	// ˳���, ��ʲôҲ���� 
						;
					}
				}
				// �����ڲ�ѭ����arr[i]����ɶ�, ��ʱֻ��i--
				i--; 
			}
			// �󶥶ѹ������
//			printf("\n�󶥶�: ");
//			for(i=0; i<arr_size; i++)printf("%d ", arr[i]);
			/**
			   �ڶ���: ÿ�ν�����Ԫ����ײ�Ԫ�ؽ���, �����ѳ�-1
			   **/
            len = arr_size;
            while(len){	// ֱ������ֻʣ1��Ԫ��ʱֹͣ, ���ѭ���������ǲ��Ͻ��󶥶ѵĶ����뵱ǰ�ѵ� 
				len--;
            	tmp = arr[len];
            	arr[len] = arr[0];
            	arr[0] = tmp;	// ������һ��Ԫ�������һ��Ԫ��
            	i = 0;
				while(2*i+1 < len){	// �ڲ�ѭ����������Ѱ�Ҹ�����ȥ�����һ��Ԫ��(��i��¼�±�)������λ��, ��ʱ���г��˶Ѷ�ȫΪ�󶥶�, ��ֹ����Ϊ��ǰ�ڵ�Ϊ��Ҷ�ڵ�, ѭ����ֹʱ���ҵ��˸�Ԫ��Ӧ���ڵ�λ�� 
					if(2*i+2 < len){	// ������Һ�������Ԫ�رȽ� 
						if(tmp >= arr[2*i+1] && tmp>= arr[2*i+2]){	// ����ǰλ�����, ���ҵ��˵ط� 
							break;
						}else{	// �������Һ����д���һ�����ڵ�ǰ 
							if(arr[2*i+1] >= arr[2*i+2]){	// ���Ӵ� 
								arr[i] = arr[2*i+1];	// ��ڵ�Ų����
								i = 2*i+1;	// ��ǰ�±�ָ���ڵ� 
							}else{	// �Һ��Ӵ� 
								arr[i] = arr[2*i+2];
								i = 2*i+2;
							}
						}
					}else{	// û�Һ������Ԫ�رȽ� 
						if(tmp < arr[2*i+1]){	// ���Ӵ� 
							arr[i] = arr[2*i+1];
							i = 2*i+1;
						}else{	// ����ǰλ�ü�Ϊ����λ�� 
							break;
						}
					}
				}
				// �ڲ�ѭ������, ��ǰ��iΪ�ո�����ȥ�Ľڵ������λ��
				arr[i] = tmp;
			}
			return;
		}
		case true:{	// ����: ����С���� 
		/**
		   ��һ��: ԭ�ع���С���� 
		   **/ 
			while(i+1){
				if(i*2+2 < arr_size){
					tmp = arr[i];
					tmp_i = i;
					while(2*tmp_i+1 < arr_size){
						if(2*tmp_i+2 < arr_size){
							if(tmp <= arr[2*tmp_i+1] && tmp <= arr[2*tmp_i+2]){
								break;
							}else{
								if(arr[2*tmp_i+1] <= arr[2*tmp_i+2]){
									arr[tmp_i] = arr[2*tmp_i+1];
									tmp_i = 2*tmp_i+1;
								}else{
									arr[tmp_i] = arr[2*tmp_i+2];	
									tmp_i = 2*tmp_i+2;
								}
							}
						}else{
							if(tmp > arr[2*tmp_i+1]){
								arr[tmp_i] = arr[2*tmp_i+1];
								tmp_i = 2*tmp_i+1;
							}else{
								break;
							}
						}
					}
					arr[tmp_i] = tmp; 
				}else{
					if(arr[i] > arr[2*i+1]){
						tmp = arr[i];
						arr[i] = arr[2*i+1];
						arr[2*i+1] = tmp;
					}else{
						;
					}
				}
				i--; 
			}
			// С���ѹ������
//			printf("\nС����: ");
//			for(i=0; i<arr_size; i++)printf("%d ", arr[i]);
			/**
			   �ڶ���: ÿ�ν�����Ԫ����ײ�Ԫ�ؽ���, �����ѳ�-1
			   **/
            len = arr_size;
            while(len){
				len--;
            	tmp = arr[len];
            	arr[len] = arr[0];
            	arr[0] = tmp;
            	i = 0;
				while(2*i+1 < len){
					if(2*i+2 < len){
						if(tmp <= arr[2*i+1] && tmp<= arr[2*i+2]){
							break;
						}else{
							if(arr[2*i+1] <= arr[2*i+2]){
								arr[i] = arr[2*i+1];
								i = 2*i+1;
							}else{
								arr[i] = arr[2*i+2];
								i = 2*i+2;
							}
						}
					}else{
						if(tmp > arr[2*i+1]){
							arr[i] = arr[2*i+1];
							i = 2*i+1;
						}else{
							break;
						}
					}
				}
				arr[i] = tmp;
			}
			return;
		}
	}
}


//______________________________________________________________________________
