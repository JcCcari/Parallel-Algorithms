#include <iostream>
using namespace std;

void MergeLow( int my_keys[], int recv_keys[], int temp_keys[], int local_n){
	int m_i, r_i, t_i;

	m_i = r_i = t_i = 0;
	while ( t_i < local_n){
		if ( my_keys[m_i] <= recv_keys[r_i]){
			temp_keys[t_i] = my_keys[m_i];
			t_i++; m_i++;
		} else {
			temp_keys[t_i] = recv_keys[r_i];
			t_i++; r_i++;
		}
	}

	for (m_i = 0; m_i < local_n ; m_i++)
		my_keys[m_i] = temp_keys[r_i];

} //Merge_low
	
