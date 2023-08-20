#include <string>

//MAKING 1-D HISTOGRAM:

void neutronsZposHist()
{   
    //*******************
    //*****INPUTS:*******
    //*******************

    double bins = 15.0; //Bins of the histogram.

    double xmin = 0.0; //X axis min value.
 
    double xmax = 50; //X axis max value.

    const char *title  = "BIASING FACTOR = 100.0";  //Insert the title of the histogram.

    const char *x_axis = "depth in um";   //X axis name.

    const char *y_axis = "neutrons generated";   //Y axis name.

    double value;   //text values 

    double parameter_fix = 10000.0; //we want the axis in um.

    int numData = 14200;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    TH1D *hist = new TH1D("hist",title, bins, xmin, xmax);

    
    //Insert the file:
    fstream file;
    file.open("neutrons_zpos_f=100.txt", ios::in);

    for( int i = 1; i <= numData; ++i)
 
    {
        file >> value; //we send the file into the parameter value (double).
        hist->Fill(value*parameter_fix); //We fill the histogram with the file values.
        if(file.eof()) break; //Stop when we reach the end of file.
    }
    


    //Splitting the histogram bins into three equal parts:
    int nbins = hist->GetNbinsX();
    int bin1 = nbins / 3;
    int bin2 = 2 * nbins / 3;
    
    //Calculate integral of each area:
    double counts1 = hist->Integral(1,bin1);
    double counts2 = hist->Integral(bin1+1,bin2);
    double counts3 = hist->Integral(bin2+1,nbins);

    //Print the A/B and A/C with A being counts1, B being counts2 and C being counts3:
    std::cout << "A/B = " << counts1/counts2 << std::endl;
    std::cout << "A/C = " << counts1/counts3 << std::endl;   
    
    
    //Always close the file:
    file.close();

    //Get the axis names:
    hist->GetXaxis()->SetTitle(x_axis);
    hist->GetYaxis()->SetTitle(y_axis);
    hist->SetFillColor(kGreen-9);
    
    //Make the canvas, named as canvas:

    TCanvas *canvas = new TCanvas();
    
    //Drawing the histogram: 
    hist->Draw();

    //Making the boundary lines between the three parts:
    double xMin = hist->GetBinLowEdge(1);
    double xMax = hist->GetBinLowEdge(nbins+1);
    double yMin = hist->GetMinimum();
    double yMax = hist->GetMaximum();

    TLine *line1 = new TLine(xMin + (xMax-xMin)*(1./3.), yMin, xMin + (xMax-xMin)*(1./3.), yMax);
    TLine *line2 = new TLine(xMin + (xMax-xMin)*(2./3.), yMin, xMin + (xMax-xMin)*(2./3.), yMax);
    
    line1->SetLineColor(kRed);
    line2->SetLineColor(kRed);
    line1->Draw();
    line2->Draw();
    canvas->Update();

}


