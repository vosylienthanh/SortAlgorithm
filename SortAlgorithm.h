/*
Họ và tên: Võ Sỹ Liên Thành
MSSV: 1512515

- Đồ án CTDL&GT: Chương trình quản lý tập tin, thư mục đơn giản.
*/
//Lớp thuật toán.

#ifndef _SORT_ALGORITHM_H_
#define _SORT_ALGORITHM_H_

#include <iostream>

using namespace std;

#pragma pack(1)
template <class ListType, class ElementType>
class CSortAlgorithm
{
protected:
	////static CSortAlgorithm *m_Instance;								//Thực thể chỉ tồn tại duy nhất.
	//void(*m_currentSortAlgorithm)(const vector<int>&);				//Con trỏ hàm trỏ đến thuật toán sắp xếp đang dữ.

	////---------------------------NHÓM PHƯƠNG THỨC TẠO, HỦY---------------------------
	////Hàm tạo.
	//CSortAlgorithm();
	////Hàm hủy.
	//~CSortAlgorithm();
public:
	//---------------------------NHÓM PHƯƠNG THỨC GET, SET---------------------------
	////Hàm lấy ra thực thể.
	//static CSortAlgorithm* getInstance(void(*)(const vector<int>&));
	////Hàm set thuật toán sort cần dùng.
	//static void setSortAlgorithm(void(*)(const vector<int>&));
	////Hàm gọi thuật toán Sort mà con trỏ *m_currentSortAlgorithm đang giữ.
	//static void Sort();

	//---------------------------NHÓM THUẬT TOÁN SORT---------------------------
	//Hàm Insertion sort.
	static void InsertionSort(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const size_t &NumOfElements);
	//Hàm Selection sort.
	static void SelectionSort(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const size_t &NumOfElements);
	//Hàm Quick sort.
	static void QuickSort(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const int &Upper, const int &Lower = 0);
	//Hàm Merge sort.
	static void MergeSort(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&),  const int &Upper, const int &Lower = 0);
	//Hàm Heap sort.
	static void HeapSort(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const size_t &NumOfElements);
	//Hàm Shell sort.
	static void ShellSort(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const size_t &NumOfElements);

private:
	//---------------------------NHÓM PHƯƠNG THỨC HỖ TRỢ ẨN---------------------------
	//Hàm tìm vị trí mốc bằng việc đưa các phần tử về đúng vị trí của nó (hỗ trợ Quick sort).
	static int Partition(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const int &Lower, const int &Upper);
	//Hàm gộp hai mảng đã được sắp xếp thành một mảng được sắp xếp (Hõ ttợ Merge sort).
	static void Merge(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const int &Lower, const int &Mid, const int &Upper);
	//Hàm tạo cây Heap.
	static void Heapify(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const size_t &NumOfElements, const int &Root = 0);
};
#endif

//---------------------------NHÓM THUẬT TOÁN SORT---------------------------
//Hàm Insertion sort.
template <class ListType, class ElementType>
void CSortAlgorithm<ListType, ElementType>::InsertionSort(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const size_t &NumOfElements)
{
	ElementType Key;
	int j;

	for (int i = 1; i < NumOfElements; i++)
	{
		Key = Src[i];
		j = i - 1;

		while (j >= 0 && cmpFunction(Src[j], Key))
		{
			Src[j + 1] = Src[j];
			--j;
		}
		Src[j + 1] = Key;
	}
}

//Hàm Selection sort.
template <class ListType, class ElementType>
void CSortAlgorithm<ListType, ElementType>::SelectionSort(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const size_t &NumOfElements)
{
	size_t AppropriateIndex;

	for (size_t i = 0; i < NumOfElements - 1; i++)
	{
		AppropriateIndex = i;

		for (size_t j = i + 1; j < NumOfElements; j++)
		{
			if (cmpFunction(Src[AppropriateIndex], Src[j]))
			{
				AppropriateIndex = j;
			}
		}

		swap(Src[i], Src[AppropriateIndex]);
	}
}

//Hàm Quick sort.
template<class ListType, class ElementType>
void CSortAlgorithm<ListType, ElementType>::QuickSort(ListType & Src, bool(*cmpFunction)(const ElementType &, const ElementType &), const int &Upper, const int &Lower)
{
	if (Lower < Upper)
	{
		int Pivot = Partition(Src, cmpFunction, Lower, Upper);

		QuickSort(Src, cmpFunction, Pivot - 1, Lower);
		QuickSort(Src, cmpFunction, Upper, Pivot + 1);
	}
}

//Hàm Merge sort.
template<class ListType, class ElementType>
void CSortAlgorithm<ListType, ElementType>::MergeSort(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const int &Upper, const int &Lower)
{
	if (Lower < Upper)
	{
		int Mid = Lower + (Upper - Lower) / 2; //Hạn chế tràn số.

		MergeSort(Src, cmpFunction, Mid, Lower);
		MergeSort(Src, cmpFunction, Upper, Mid + 1);

		Merge(Src, cmpFunction, Lower, Mid, Upper);
	}
}

//Hàm Heap sort.
template<class ListType, class ElementType>
void CSortAlgorithm<ListType, ElementType>::HeapSort(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const size_t &NumOfElements)
{
	//Bước đầu xây dựng cây Heap từ dưới lên.
	for (int i = (NumOfElements / 2) - 1; i >= 0; i--)
	{
		Heapify(Src, cmpFunction, NumOfElements, i);
	}

	//Hoán vị phần tử đầu và cuối sau đó xây lại cây heap.
	for (int i = NumOfElements - 1; i >= 0; i--)
	{
		swap(Src[0], Src[i]);

		Heapify(Src, cmpFunction, i);
	}
}

//Hàm Shell sort.
template<class ListType, class ElementType>
void CSortAlgorithm<ListType, ElementType>::ShellSort(ListType & Src, bool(*cmpFunction)(const ElementType &, const ElementType &), const size_t & NumOfElements)
{
	int Key;
	int j;

	//Xác định gap.
	for (int gap = NumOfElements / 2; gap > 0; gap = gap / 2)
	{
		//Tiến hành Insertion Sort
		for (int i = gap; i < NumOfElements; i++)
		{
			Key = Src[i];
			j = i;

			while (j >= gap && cmpFunction(Src[j - gap], Key))
			{
				Src[j] = Src[j - gap];
				j = j - gap;
			}
			Src[j] = Key;
		}
	}
}

//---------------------------NHÓM PHƯƠNG THỨC HỖ TRỢ ẨN---------------------------
//Hàm tìm vị trí mốc bằng việc đưa các phần tử về đúng vị trí của nó (hỗ trợ Quick sort).
template<class ListType, class ElementType>
int CSortAlgorithm<ListType, ElementType>::Partition(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const int &Lower, const int &Upper)
{
	int curr = Lower - 1;
	ElementType Pivot = Src[Upper];

	for (size_t i = Lower; i < Upper; i++)
	{
		if (!cmpFunction(Src[i], Pivot)) //Nếu Src[i] và Pivot không nghịch thế.
		{
			++curr;
			swap(Src[i], Src[curr]);
		}
	}
	swap(Src[curr + 1], Src[Upper]);

	return (curr + 1);
}

//Hàm gộp hai mảng đã được sắp xếp thành một mảng được sắp xếp (Hõ ttợ Merge sort).
template<class ListType, class ElementType>
void CSortAlgorithm<ListType, ElementType>::Merge(ListType &Src, bool(*cmpFunction)(const ElementType &, const ElementType &), const int &Lower, const int &Mid, const int &Upper)
{
	size_t n1 = Mid - Lower + 1;
	size_t n2 = Upper - Mid;
	ElementType *Left = new ElementType[n1]; //Mảng phụ bên trái.
	ElementType *Right = new ElementType[n2]; //Mảng phụ bên phải.
	int i, j, k;
	k = Lower;

	//Chuyển sang mảng phụ.
	for (i = 0; i < n1; i++)
	{
		Left[i] = Src[Lower + i];
	}
	for (j = 0; j < n2; j++)
	{
		Right[j] = Src[Mid + j + 1];
	}

	//Trộn.
	i = j = 0;
	while (i < n1 && j < n2)
	{
		if (!cmpFunction(Left[i], Right[j]))
		{
			Src[k] = Left[i];
			++i;
		}
		else
		{
			Src[k] = Right[j];
			++j;
		}
		++k;
	}

	while (i < n1)
	{
		Src[k] = Left[i];
		++k;
		++i;
	}
	while (j < n2)
	{
		Src[k] = Right[j];
		++k;
		++j;
	}

	delete[]Left;
	delete[]Right;
}

//Hàm tạo cây Heap.
template<class ListType, class ElementType>
void CSortAlgorithm<ListType, ElementType>::Heapify(ListType &Src, bool(*cmpFunction)(const ElementType&, const ElementType&), const size_t &NumOfElements, const int &Root)
{
	int Left = 2 * Root + 1;
	int Right = Left + 1;
	int Index = Root;

	//Tìm vị trí lớn nhất.
	if (Left < NumOfElements && cmpFunction(Src[Left], Src[Index]))
	{
		Index = Left;
	}
	if (Right < NumOfElements && cmpFunction(Src[Right], Src[Index]))
	{
		Index = Right;
	}

	//Nếu vị trí tìm được khác Root => Hoán vị và tipế tục tạo cây Heap cho nhánh vừa hoán vị.
	if (Index != Root)
	{
		swap(Src[Index], Src[Root]);
		Heapify(Src, cmpFunction, NumOfElements, Index);
	}
}