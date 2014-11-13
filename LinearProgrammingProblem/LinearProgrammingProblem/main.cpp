//
//  main.cpp
//  LinearProgrammingProblem
//
//  Created by Lu Kuan-Yin on 11/10/14.
//  Copyright (c) 2014 NTU. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

#include "LinearFunction.h"

#define NEGATIVE_INFINITY 234567
int zeroXindex;

using namespace std;

void Initial_Input(vector<LinearFuntion> &FunctionList)
{
    FILE *fp = fopen("/AlgorithmTestData/FunctionInput3.txt", "r");
    if (!fp) {
        cout<<"File cannot be found!!\n";
    }
    LinearFuntion temp;
    while (fscanf(fp, "%f %f %f\n", &temp.Xcoef, &temp.Ycoef, &temp.constant) == 3) {
        //cout<<"Context : "<<temp.Xcoef<<temp.Ycoef<<temp.constant<< endl;
        FunctionList.push_back(temp);
    }
    
}

void Find_All_Intersection_Point(const vector<LinearFuntion> &FunctionList,
                                 vector<pair<float, float>> &PointList)
{
    pair<float, float> IntersectionPoint;
    LinearFuntion Line1,Line2, LineSub;
    
    for (int i=0; i<FunctionList.size(); i++) {
        for (int j=i+1; j<FunctionList.size(); j++) {
            
            //若FunctionList[i] x的係數=0時...
            if (FunctionList[i].Xcoef == 0) {
                IntersectionPoint.second = FunctionList[i].constant/FunctionList[i].Ycoef;
                IntersectionPoint.first = (FunctionList[j].constant - FunctionList[j].Ycoef*IntersectionPoint.second)/FunctionList[j].Xcoef;
                
                printf("( %.2f,  %.2f)\n", IntersectionPoint.first, IntersectionPoint.second);
                zeroXindex = (int)PointList.size();//判斷NEGATIVE_INFINITY
                PointList.push_back(IntersectionPoint);
                continue;
            }
            //若FunctionList[j] x的係數=0時...
            else if (FunctionList[j].Xcoef == 0) {
                IntersectionPoint.second = FunctionList[j].constant/FunctionList[j].Ycoef;
                IntersectionPoint.first = (FunctionList[i].constant - FunctionList[i].Ycoef*IntersectionPoint.second)/FunctionList[i].Xcoef;
                
                printf("( %.2f,  %.2f)\n", IntersectionPoint.first, IntersectionPoint.second);
                zeroXindex = (int)PointList.size(); //判斷NEGATIVE_INFINITY
                PointList.push_back(IntersectionPoint);
                continue;
            }
            
            
            Line1.Xcoef = FunctionList[i].Xcoef *FunctionList[j].Xcoef;
            Line1.Ycoef = FunctionList[i].Ycoef *FunctionList[j].Xcoef;
            Line1.constant = FunctionList[i].constant *FunctionList[j].Xcoef;
            
            Line2.Xcoef = FunctionList[j].Xcoef *FunctionList[i].Xcoef;
            Line2.Ycoef = FunctionList[j].Ycoef *FunctionList[i].Xcoef;
            Line2.constant = FunctionList[j].constant * FunctionList[i].Xcoef;
            
            LineSub.Xcoef = Line1.Xcoef - Line2.Xcoef;
            LineSub.Ycoef = Line1.Ycoef - Line2.Ycoef;
            LineSub.constant = Line1.constant - Line2.constant;
            
            IntersectionPoint.second = LineSub.constant / LineSub.Ycoef;
            IntersectionPoint.first = (FunctionList[i].constant -
                                       FunctionList[i].Ycoef*IntersectionPoint.second)/FunctionList[i].Xcoef;
            
            PointList.push_back(IntersectionPoint);
            printf("( %.2f,  %.2f)\n", IntersectionPoint.first, IntersectionPoint.second);
        }
    }
    //cout<<"size:"<< PointList.size()<<endl;
}

float Find_min_Y(const vector<pair<float, float>> &PointList, vector<LinearFuntion> &FunctionList)
{
    bool X_coef_Zero = false;
    float Ymin=0;
    
    //先找有沒有x係數等於0的
    for (int i=0; i<FunctionList.size(); i++) {
        if (FunctionList[i].Xcoef == 0) {
            Ymin = PointList[zeroXindex].second;
            X_coef_Zero = true;
            break;
        }
    }
    
    if (X_coef_Zero == true) {
        bool less_Ymin = false;
        for (int j=0; j<PointList.size(); j++) {
            if( PointList[j].second < Ymin) {
                less_Ymin = true;
            }
        }
        if ( less_Ymin == false )
            return NEGATIVE_INFINITY;
    }
    
    
    Ymin = PointList[0].second;
    for (int i=1; i<PointList.size(); i++) {
        if (PointList[i].second < Ymin) {
            Ymin = PointList[i].second;
        }
    }
    return Ymin;
}

//============================for Unit Test==================================
void Print_functionList(vector<LinearFuntion> &FunctionList)
{
    for (vector<LinearFuntion>::iterator it = FunctionList.begin(); it != FunctionList.end(); it++) {
        printf("%f %f %f\n",(*it).Xcoef, (*it).Ycoef, (*it).constant);
    }
}
//===========================================================================

int main(int argc, const char * argv[])
{
    vector<LinearFuntion> FunctionList;
    vector<pair<float, float>> IntersectionPointList;
    
    Initial_Input(FunctionList);
    //Print_functionList(FunctionList);
    Find_All_Intersection_Point(FunctionList, IntersectionPointList);
    float Ymin = Find_min_Y(IntersectionPointList, FunctionList);
    if (Ymin == NEGATIVE_INFINITY) {
        cout<<"Negative infinity!\n";
    }
    else {
        cout << "Result : "<<Ymin<< endl;
    }
    
    
    return 0;
}
