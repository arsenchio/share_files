//
// Created by Арсентий on 15.10.17.
//

#ifndef TRADING_MYLIB_H
#define TRADING_MYLIB_H


#include <vector>

typedef std::vector< std::vector<float > > MATRIX;


class MyLib {
public:
  float min (const std::vector<float > & v, int start_idx, int end_idx);
  float max (const std::vector<float > & v, int start_idx, int end_idx);

  float mean (const std::vector<float > & v, int start_idx, int end_idx);
  float var (const std::vector<float > & v, int start_idx, int end_idx);
  float std (const std::vector<float > & v, int start_idx, int end_idx);

  float sMA (const std::vector<float > & v, int start_idx, int end_idx);
  float eMA (const std::vector<float > & v, int start_idx, int end_idx, float alpha = -1.0f);
  float weightedMA (const std::vector<float > & v, const std::vector<float > & weights, int start_idx, int end_idx);
  float variableMA (const std::vector<float > & v,
                    const std::vector<float > & volatility_index,
                    int start_idx, int end_idx,
                    float alpha = -1.0f);


  float meanAbsDeviation (const std::vector<float > & v, int start_idx, int end_idx);

  float rateOfChange (float current, float prev);


  /*
   * Trend strength
   */
  // Usually too slow
  float averageDirectionalIndex (const std::vector<float> &high,
                                 const std::vector<float> &low,
                                 const std::vector<float> &true_range,
                                 int dx_window = 3,
                                 int di_window = 14,
                                 int true_range_window = 10);
  float reverseArrangementTest (const std::vector<float > & close, int start_idx, int end_idx);
  // Ad-hoc
  // 1. Wait another day to confirm indicator value
  // 2. MA channel
  // 3. Triple MA cross
  // float hysteresis ();

  /*
   * Reversion
   */
  struct BollingerBands {
    float upper;
    float middle;
    float lower;
    BollingerBands(float up, float mid, float low): upper(up), lower(low), middle(mid) {};
  };
  BollingerBands bollingerBands(const std::vector<float > & close, int start_idx, int end_idx, float K=2);
  float z_score (const std::vector<float > & close, int start_idx, int end_idx);
  float bollingerRelative (const std::vector<float> &close, int start_idx, int end_idx, float K=2);

  float RSI (const std::vector<float > & close);

  // Oscillators
  struct Oscillators {
    float fastK;
    float fastD;
    float fullD;
    Oscillators (float fK, float fD, float flD): fastK(fK), fastD(fD), fullD(flD) {}
  };

  Oscillators oscillators (const std::vector<float> &high,
                           const std::vector<float> &low,
                           const std::vector<float> &close,
                           int d_window, int min_max_window = 14);

  // Volume-adjusted
  float onBalanceVolume (const std::vector<float > & close, const std::vector<float > & volume);
  float chaikinMoneyFlow (const std::vector<float > & high,
                          const std::vector<float > & low,
                          const std::vector<float > & close,
                          const std::vector<float > & volume);
  float moneyFlowIndex (const std::vector<float > & true_price, const std::vector<float > & volume);



};


#endif //TRADING_MYLIB_H
