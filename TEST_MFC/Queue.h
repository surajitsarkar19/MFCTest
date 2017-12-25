#pragma once

template <class T>
class CQueue :public CTypedPtrList< CPtrList, T* >
{
public:
	CQueue(void){};
	~CQueue(void)
	{
		if(GetCount()>0)
		{
			POSITION pos;
			pos=GetHeadPosition();
			do
			{
			   //display first image.then set timer
			   T *str = GetNext(pos);
			   delete str;
			}while(pos!=NULL);
		}
	};
	// Go to the end of the line
    void Push( T* data )
    { 
		AddTail( data ); 
	}        // End of the queue

    // Get first element in line
    T* Pop()
    { 
		return IsEmpty() ? NULL : RemoveHead(); 
	}
};
