#ifndef COEFFS_H
#define COEFFS_H

struct Coeffs {
  Coeffs(double a,
         double b,
         double c)
  {
    A = a; B = b; C = c;
  }

  double A, B, C;
};

class CoeffsEstimator
{
  public:
    CoeffsEstimator();

    const Coeffs& getCoeffs() {return coeffs;}

    void addRlsData();

  private:
    Coeffs coeffs;
};

#endif // COEFFS_H
