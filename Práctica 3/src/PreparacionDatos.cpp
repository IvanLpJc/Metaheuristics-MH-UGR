#include "PreparacionDatos.h"

void checkSize(const char* filename, int &num_muestras, int &num_caracteristicas){
	if (strcmp(filename, "./Data/parkinsons.arff") == 0){
	    num_muestras = 195;
        num_caracteristicas = 22;
  	} else if (strcmp(filename, "./Data/ozone-320.arff") == 0){
        num_muestras = 320;
        num_caracteristicas = 72;
    } else if (strcmp(filename, "./Data/spectf-heart.arff") == 0){
        num_muestras = 349;
        num_caracteristicas = 44;
    }
}



void leerConjunto(vector<vector<float>> &data, const char* filename){

	int num_muestras = 0 , num_caracteristicas = 0 ;
	data.resize(0) ;
	checkSize(filename, num_muestras, num_caracteristicas) ;
	
	data.resize(num_muestras) ;


	for(int i = 0 ; i < num_muestras; i++){
		data[i].resize(num_caracteristicas+1) ;
	}
	ifstream file(filename) ;

	std::string line ;
	std::getline(file,line); 
	while(line != "@data"){
		std::getline(file,line) ;
	}

	for(int row = 0 ; row < num_muestras ; row++){

		std::getline(file,line) ;
		stringstream iss(line) ;

		for(int col = 0 ; col <= num_caracteristicas ; col++){
			std::string val ;
			std::getline(iss,val,',') ;
			stringstream convertor(val) ;
			convertor >> data[row][col] ;
		}
	}
    Normalizar(data) ;
}

void muestraDatos(vector<vector<float>> &datos){
	for(int i = 0 ; i < datos.size() ; i++){
		for(int j = 0 ; j < datos[0].size() ; ++j){
			cout << "|" << datos[i][j] ;
		}
		cout << endl ;
	}

	cout << "=============================================" << endl ;
	cout << "características: " << datos[0].size() << "; muestras: " << datos.size() << endl ;;
}

void muestraDatos(list<vector<float>> &datos){
	list<vector<float>>::iterator it ;

	for(it = datos.begin() ; it != datos.end() ; it++){
		for(int j = 0 ; j < (*it).size() ; ++j){
			cout << "|" << (*it)[j] ;
		}
		cout << endl ;
	}

	cout << "=============================================" << endl ;
	cout << "características: " << (*(datos.begin())).size() << "; muestras: " << datos.size() << endl ;;
}
void Normalizar(vector<vector<float>> &data){

    for(int col = 0 ; col < data[0].size()-1 ; ++col){
        float min = 99999, max = 0 ;
        for(int row = 0 ; row < data.size() ; row++){
            if(data[row][col] > max)
                max = data[row][col] ;
            if(data[row][col] < min)
                min = data[row][col] ;
        }
        for(int row = 0 ; row < data.size() ; row++){
            data[row][col] = (data[row][col] - min) / (max - min) ;
        }
    }
}

void CargarDatos(vector<vector<float>> &data, int bd){
	switch(bd){
        case 1 :
        	leerConjunto(data, "./Data/parkinsons.arff") ;
            break ;
        case 2:
			leerConjunto(data, "./Data/ozone-320.arff") ;
			break ;
        case 3:
            leerConjunto(data, "./Data/spectf-heart.arff") ;
            break ;
    }
}

void PreparaParticiones(vector<vector<float>> &data, vector<vector<float>> &conjunto1, vector<vector<float>> &conjunto2, vector<vector<float>> &conjunto3, vector<vector<float>> &conjunto4, vector<vector<float>> &conjunto5){
	int c1 = 0,c2 = 0 ;
	int num_caracteristicas = data[0].size() -1;
	int num_muestras = data.size() ;
	list<vector<float>> clase1, clase2 ;

	for(int i = 0 ; i < num_muestras ; i++){
		if(data[i].back() == 1){
			clase1.push_back(data[i]) ;
		} 
		if (data[i].back() == 2){
			clase2.push_back(data[i]) ; 
		}
	}

	int tamanio_conjunto = ceil(num_muestras*0.2) ;
	int cont_clase_1 = 0 ;
	int cont_clase_2 = 0 ;
	int p_c1 = (clase1.size()*0.2) ;
	int p_c2 = ceil(clase2.size()*0.2) ;

	conjunto1.reserve(tamanio_conjunto) ;
	conjunto2.reserve(tamanio_conjunto) ;
	conjunto3.reserve(tamanio_conjunto) ;
	conjunto4.reserve(tamanio_conjunto) ;
	conjunto5.reserve(tamanio_conjunto) ;

	for(int i = 0 ; i < tamanio_conjunto ; i++){
		conjunto1[i].reserve(num_caracteristicas+1) ;
		conjunto2[i].reserve(num_caracteristicas+1) ;
		conjunto3[i].reserve(num_caracteristicas+1) ;
		conjunto4[i].reserve(num_caracteristicas+1) ;
		conjunto5[i].reserve(num_caracteristicas+1) ;
	}

	int cont = 0 ;
	int limite = 0 ;

	for(int conjunto = 1 ; conjunto < 6 ; conjunto++){
		limite += tamanio_conjunto ;

		while(cont < limite){
			switch(conjunto){
				case 1 :
					if(clase1.empty() && !clase2.empty()){
						conjunto1.push_back(clase2.front()) ;
						clase2.pop_front() ;
						cont_clase_2++ ;
						cont++ ;
					} else if(clase2.empty() && !clase1.empty()){
						conjunto1.push_back(clase1.front()) ;
						clase1.pop_front() ;
						cont_clase_1++ ;
						cont++ ;
					} else if(cont_clase_1 < p_c1 && cont < limite){
						conjunto1.push_back(clase1.front()) ;
						clase1.pop_front() ;
						cont_clase_1++ ;
						cont++ ;
					} else if(cont_clase_2 < p_c2 && cont < limite){
						conjunto1.push_back(clase2.front()) ;
						clase2.pop_front() ;
						cont_clase_2++ ;
						cont++ ;
					}
					break ;
				case 2:
					if(clase1.empty() && !clase2.empty()){
						conjunto1.push_back(clase2.front()) ;
						clase2.pop_front() ;
						cont_clase_2++ ;
						cont++ ;
					} else if(clase2.empty() && !clase1.empty()){
						conjunto1.push_back(clase1.front()) ;
						clase1.pop_front() ;
						cont_clase_1++ ;
						cont++ ;
					} else if(cont_clase_1 < p_c1 && cont < limite){
						conjunto2.push_back(clase1.front()) ;
						clase1.pop_front() ;
						cont_clase_1++ ;
						cont++ ;
					} else if(cont_clase_2 < p_c2 && cont < limite){
						conjunto2.push_back(clase2.front()) ;
						clase2.pop_front() ;
						cont_clase_2++ ;
						cont++ ;
					}
					break ;
				case 3:
					if(clase1.empty() && !clase2.empty()){
						conjunto1.push_back(clase2.front()) ;
						clase2.pop_front() ;
						cont_clase_2++ ;
						cont++ ;
					}else if(clase2.empty() && !clase1.empty()){
						conjunto1.push_back(clase1.front()) ;
						clase1.pop_front() ;
						cont_clase_1++ ;
						cont++ ;
					}else if(cont_clase_1 < p_c1 && cont < limite){
						conjunto3.push_back(clase1.front()) ;
						clase1.pop_front() ;
						cont_clase_1++ ;
						cont++ ;
					} else if(cont_clase_2 < p_c2 && cont < limite){
						conjunto3.push_back(clase2.front()) ;
						clase2.pop_front() ;
						cont_clase_2++ ;
						cont++ ;
					}
					break ;
				case 4:
					if(clase1.empty() && !clase2.empty()){
						conjunto1.push_back(clase2.front()) ;
						clase2.pop_front() ;
						cont_clase_2++ ;
						cont++ ;
					} else if(clase2.empty() && !clase1.empty()){
						conjunto1.push_back(clase1.front()) ;
						clase1.pop_front() ;
						cont_clase_1++ ;
						cont++ ;
					} else if(cont_clase_1 < p_c1 && cont < limite){
						conjunto4.push_back(clase1.front()) ;
						clase1.pop_front() ;
						cont_clase_1++ ;
						cont++ ;
					}else if(cont_clase_2 < p_c2 && cont < limite){
						conjunto4.push_back(clase2.front()) ;
						clase2.pop_front() ;
						cont_clase_2++ ;
						cont++ ;
					}
					break ;
				case 5:
					if(clase1.empty() && !clase2.empty()){
						conjunto5.push_back(clase2.front()) ;
						clase2.pop_front() ;
						cont_clase_2++ ;
						cont++ ;
					} else if(clase2.empty() && !clase1.empty()){
						conjunto5.push_back(clase1.front()) ;
						clase1.pop_front() ;
						cont_clase_1++ ;
						cont++ ;
					} else if(cont_clase_1 < p_c1 && cont < limite){
						conjunto5.push_back(clase1.front()) ;
						clase1.pop_front() ;
						cont_clase_1++ ;
						cont++ ;
					} else if(cont_clase_2 < p_c2 && cont < limite){
						conjunto5.push_back(clase2.front()) ;
						clase2.pop_front() ;
						cont_clase_2++ ;
						cont++ ;
					}
					break ;
			}			
		}
		cont_clase_2 = 0;
		cont_clase_1 = 0;
	}
}

void ObtenerClase(vector<vector<float>> &data, vector<int> &clases){
	clases.reserve(data.size()) ;

	for(int row = 0 ; row < data.size() ; row++){
		clases.push_back(data[row].back()) ;
		data[row].pop_back() ;
	}
}

void Agrupa(vector<vector<float>> &datos, const vector<vector<float>> &conjunto1, const vector<vector<float>> &conjunto2, const vector<vector<float>> &conjunto3, const vector<vector<float>> &conjunto4){
	vector<vector<float>> tmp;
	srand(time(NULL));

	for(int i = 1 ; i < 5 ; i++){
		switch(i){
			case 1:
				tmp.insert(tmp.end(), conjunto1.begin(), conjunto1.end()) ;
				break;
			case 2: 
				tmp.insert(tmp.end(), conjunto2.begin(), conjunto2.end()) ;
				break;
			case 3:
				tmp.insert(tmp.end(), conjunto3.begin(), conjunto3.end()) ;
				break;
			case 4 :
				tmp.insert(tmp.end(), conjunto4.begin(), conjunto4.end()) ;
				break;
		}
	}	
	
	int random ;
    for (int i=0 ;i < tmp.size() ;++i){ 
    	vector<float> aux ;
        random = rand()%tmp.size() ;
        aux=tmp[i]; 
        tmp[i]=tmp[random]; 
        tmp[random]=aux; 
    }
	datos = tmp ;
}