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
	printf("\n原数组: ");
	for(i=0; i<TEST_NUM; i++){
		printf("%d ", a[i]);
	}
	printf("\n大顶堆: ");
	for(i=1; i<=max->length; i++){
		printf("%d ", max->data[i]);
	}
	printf("\n小顶堆: ");
	for(i=1; i<=min->length; i++){
		printf("%d ", min->data[i]);
	}
	printf("\n大顶堆pop: ");
	for(i=1; i<max->length;){
		printf("%d ", popHeap(max));
	}
	printf("\n小顶堆pop: ");
	for(i=1; i<min->length;){
		printf("%d ", popHeap(min));
	}
	printf("\n");
	heap = createHeapFromArray(a, TEST_NUM, 0, true);
	printf("从数组创建: ");
	for(i=1; i<=heap->length; i++){
		printf("%d ", heap->data[i]);
	}
	printf("\nheap pop: ");
	for(i=0; i<heap->length;){
		printf("%d ", popHeap(heap));
	}
	arrayHeapSort(a, TEST_NUM, false);
	printf("\n堆排序数组: ");
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
		printf("最大堆容量小于元素总数\n");
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
				printf("大于大顶堆最大值，插入失败！\n");
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
				printf("小于大顶堆最大值，插入失败！\n");
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
		printf("堆空\n");
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


void arrayHeapSort(ElementType *arr, int arr_size, bool reserve){// 原地堆排序 
	int i = arr_size / 2 - 1;	// i是从第一个有孩子的结点还是 
	int len, tmp_i;
	ElementType tmp;
	if(arr_size <= 1){
		printf("无需排序\n");
		return;
	}
	switch(reserve){	
		case false:{	// 正序: 构造大顶堆 
		/**
		   第一步: 原地构造大顶堆
		   **/ 
			while(i+1){	// 外层循环是从第一个有孩子的结点开始, 每次--, 将当前二叉树构造成大顶堆, 如果到0则最后一次进入循环构造 
				if(i*2+2 < arr_size){	// 如果当前节点有右孩子 (一定有左孩子), 则三元素判断 
					tmp = arr[i];	// 保存当前节点
					tmp_i = i;		// 并记住i值 
					while(2*tmp_i+1 < arr_size){	// 内层循环将当前二叉树构造成大顶堆, 最终找到的tmp_i为i应当在的位置, 终止条件为当前节点为非叶节点
						if(2*tmp_i+2 < arr_size){	// 有右孩子, 正常判断 
							if(tmp >= arr[2*tmp_i+1] && tmp >= arr[2*tmp_i+2]){	// 如果当前节点大于两个子节点则说明找到tmp_i应当在的位置了 
								break;
							}else{	// 否则没有找到, 继续向下寻找, 左右孩子中大节点一定大于当前节点 
								if(arr[2*tmp_i+1] >= arr[2*tmp_i+2]){	// 左节点大 
									arr[tmp_i] = arr[2*tmp_i+1];	// 大节点挪上来
									tmp_i = 2*tmp_i+1;	// tmp_i移向大节点 
								}else{	// 右节点大
									arr[tmp_i] = arr[2*tmp_i+2];	
									tmp_i = 2*tmp_i+2;
								}
							}
						}else{	// 没右孩子, 则只需判断当前节点与左节点 
							if(tmp < arr[2*tmp_i+1]){	// 当前节点小于左节点则交换, 否则找到 
								arr[tmp_i] = arr[2*tmp_i+1];
								tmp_i = 2*tmp_i+1;
							}else{
								break;
							}
						}
					}
					// 经过内层循环已经找到tmp_i应当的位置, 并且除了应当的位置之外其余的元素都调整好了, 所以这里只需要把tmp移过来即可
					arr[tmp_i] = tmp; 
				}else{	// 如果当前节点无右孩子, 则二元素判断, 且其左孩子一定为叶节点, 即只需判断当前位置与其左孩子构成的树是否为堆 
					if(arr[i] < arr[2*i+1]){	// 顺序不对, 调整 
						tmp = arr[i];
						arr[i] = arr[2*i+1];
						arr[2*i+1] = tmp;
					}else{	// 顺序对, 则什么也不做 
						;
					}
				}
				// 整个内层循环将arr[i]构造成堆, 此时只需i--
				i--; 
			}
			// 大顶堆构造完成
//			printf("\n大顶堆: ");
//			for(i=0; i<arr_size; i++)printf("%d ", arr[i]);
			/**
			   第二步: 每次将顶部元素与底部元素交换, 并将堆长-1
			   **/
            len = arr_size;
            while(len){	// 直到堆中只剩1个元素时停止, 外层循环的作用是不断将大顶堆的顶放入当前堆底 
				len--;
            	tmp = arr[len];
            	arr[len] = arr[0];
            	arr[0] = tmp;	// 交换第一个元素与最后一个元素
            	i = 0;
				while(2*i+1 < len){	// 内层循环的作用是寻找刚移上去的最后一个元素(用i记录下标)的真正位置, 此时堆中除了堆顶全为大顶堆, 终止条件为当前节点为非叶节点, 循环终止时则找到了该元素应当在的位置 
					if(2*i+2 < len){	// 如果有右孩子则三元素比较 
						if(tmp >= arr[2*i+1] && tmp>= arr[2*i+2]){	// 若当前位置最大, 则找到了地方 
							break;
						}else{	// 否则左右孩子中大者一定大于当前 
							if(arr[2*i+1] >= arr[2*i+2]){	// 左孩子大 
								arr[i] = arr[2*i+1];	// 大节点挪上来
								i = 2*i+1;	// 当前下标指向大节点 
							}else{	// 右孩子大 
								arr[i] = arr[2*i+2];
								i = 2*i+2;
							}
						}
					}else{	// 没右孩子则二元素比较 
						if(tmp < arr[2*i+1]){	// 左孩子大 
							arr[i] = arr[2*i+1];
							i = 2*i+1;
						}else{	// 否则当前位置即为待查位置 
							break;
						}
					}
				}
				// 内层循环结束, 当前的i为刚刚移上去的节点的真正位置
				arr[i] = tmp;
			}
			return;
		}
		case true:{	// 逆序: 构造小顶堆 
		/**
		   第一步: 原地构造小顶堆 
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
			// 小顶堆构造完成
//			printf("\n小顶堆: ");
//			for(i=0; i<arr_size; i++)printf("%d ", arr[i]);
			/**
			   第二步: 每次将顶部元素与底部元素交换, 并将堆长-1
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
