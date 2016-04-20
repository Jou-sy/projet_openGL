/*
 * CPoint2.cpp
 *
 *  Created on: 22 déc. 2009
 *      Author: girouxi
 */

#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/CData2i.h"
#include "/Users/Sylvain/Documents/ENSG/opengl/test_20_12/headers/consts.h"
CData2i::CData2i(int x, int y):colonne_1(x), colonne_2(y) {
}
CData2i::CData2i():colonne_1(NOVAL), colonne_2(NOVAL) {
}
CData2i::CData2i(const CData2i &data2i):colonne_1(data2i.colonne_1), colonne_2(data2i.colonne_2){

}
