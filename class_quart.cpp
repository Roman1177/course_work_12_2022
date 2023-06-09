//---------------------------------------------------------------------------

#pragma hdrstop

#include "class_quart.h"
//---------------------------------------------------------------------------
	void Quarter::set_row(int const val){
		if(val >= 0){
			row = val;
		}else{
		   row = 0;
		}
	}
	void Quarter::set_max_value(int const val){
		max_value =val;
	}


	void Quarter::set_flag(bool const fg){
		flag_st = fg;
	}

	void Quarter::set_type_flag(bool const fg){
		type_file = fg;
	}

	void Quarter::set_error_flag(bool const fg){
		date_ERROR_f = fg;
	}

	void Quarter::set_address(AnsiString const addr){  //        поставить константы
		file_address = addr;
	}
/*    void Quarter::set_address(string const addr){  //        поставить константы
		file_address = addr;
	}
*/
	void Quarter::set_quart(Variant const val){
		quart = val;
	}

	void Quarter::set_max_work(int const val){
		if(val>0){
			max_work = val;
		}else{
			max_work = 0;
		}
	}

//---------------------------------------------------------------------------
	int Quarter::get_row(){
		return (row);
	}
	int Quarter::get_max_value(){
		return (max_value);
	}

	int Quarter::get_counter_row(){
		return counter_row;
	}

	int Quarter::get_col(){
		return (column);
	}

	int Quarter::get_max_work(){
		return(max_work);
	}

	bool Quarter::get_flag(){
		return (flag_st);
	}

	bool Quarter::get_type_flag(){
		return (type_file);
	}

	bool Quarter::get_error_flag(){
		return (date_ERROR_f);
	}

	AnsiString Quarter::get_file_addr(){
		return (file_address);
	}
	/*
	string Quarter::get_file_addr(){
		return (file_address);
	}*/

	Variant Quarter::get_quart(){
		return (quart);
	}
//---------------------------------------------------------------------------
	 void Quarter::exit_Excel(){
		quart.OleProcedure("Quit");
		quart = Unassigned;
	 }


	 void Quarter::inc_row(){
		++row;
	 }

	 void Quarter::inc_counter_row(){
		++counter_row;
	 }


	 void Quarter::dec_row(){
		--row;
		 if(row < 0){
			row = 0;
		}
	 }

	 void Quarter::delete_row(){
		row = 0;
	 }

//---------------------------------------------------------------------------
#pragma package(smart_init)
