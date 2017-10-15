//
// Created by Арсентий on 15.10.17.
//

#include <cmath>
#include <cassert>
// #include <limits>
#include "MyLib.h"


float MyLib::min(const std::vector<float> &v, int start_idx, int end_idx) {
  float m = std::numeric_limits<float>::max();
  for (int ii = start_idx; ii < end_idx; ++ii) {
    if (v[ii] < m) {
      m = v[ii];
    }
  }
  return m;
}


float MyLib::max(const std::vector<float> &v, int start_idx, int end_idx) {
  float m = std::numeric_limits<float>::min();
  for (int ii = start_idx; ii < end_idx; ++ii) {
    if (v[ii] > m) {
      m = v[ii];
    }
  }
  return m;
}


float MyLib::mean(const std::vector<float> &v, int start_idx, int end_idx) {
  float res = 0;
  for (int di = start_idx; di < end_idx; ++di) {
    res += v[di];
  }
  return res / static_cast<float >(end_idx - start_idx);
}


float MyLib::var(const std::vector<float> &v, int start_idx, int end_idx) {
  float m = mean(v, start_idx, end_idx);
  float sum_of_squares = 0;
  for (int di = start_idx; di < end_idx; ++di) {
    sum_of_squares += v[di]*v[di];
  }
  return (sum_of_squares -  m*m / static_cast<float >(end_idx - start_idx) ) /
          static_cast<float >(end_idx - start_idx - 1);
}


float MyLib::std(const std::vector<float> &v, int start_idx, int end_idx) {
  return sqrt(var(v, start_idx, end_idx) );
}


float MyLib::sMA(const std::vector<float> &v, int start_idx, int end_idx) {
  float res = 0;
  for (int di = start_idx; di < end_idx; ++di) {
    res += v[di];
  }
  return res / static_cast<float >(end_idx - start_idx);
}


float MyLib::eMA(const std::vector<float> &v, int start_idx, int end_idx, float alpha) {
  if (alpha < 0) {
    alpha = 1.0f /static_cast<float >(end_idx-start_idx);
  }
  float res = 0;
  for (int di = start_idx; di < end_idx; ++di) {
    res += alpha*v[di] + (1-alpha)*res;
  }
  return res;
}


float MyLib::weightedMA(const std::vector<float> &v, const std::vector<float> &weights, int start_idx, int end_idx) {
  float res = 0;
  float total_weight = 0;
  for (int di = start_idx; di < end_idx; ++di) {
    res += weights[di - start_idx]*v[di];
    total_weight += weights[di - start_idx];
  }
  return res / total_weight;
}


float MyLib::variableMA(const std::vector<float> &v,
                        const std::vector<float> &volatility_index,
                        int start_idx,
                        int end_idx,
                        float alpha) {
  if (alpha < 0) {
    alpha = 1.0f /static_cast<float >(end_idx-start_idx);
  }
  float res = 0;
  for (int di = start_idx; di < end_idx; ++di) {
    res += (alpha*volatility_index[di])*v[di] + (1-alpha*volatility_index[di])*res;
  }
  return res;
}


float MyLib::meanAbsDeviation(const std::vector<float> &v, int start_idx, int end_idx) {
  float res = 0;
  float m = mean(v, start_idx, end_idx);
  for (int di = start_idx; di < end_idx; ++di) {
    res += fabs(v[di] - m);
  }
  return res / static_cast<float >(end_idx - start_idx);
}


float MyLib::rateOfChange(float current, float prev) {
  return (current - prev) / prev;
}

/*
 * --------------   -------------    -----------
 * true_range_avg | di/atr average | avg of index
 * So true_range, high and low should have length = di_window + true_range_window + di_window - 2
 */
float MyLib::averageDirectionalIndex(const std::vector<float> &high,
                                     const std::vector<float> &low,
                                     const std::vector<float> &true_range,
                                     int dx_window,
                                     int di_window,
                                     int true_range_window) {
  assert( true_range.size() - di_window - true_range_window - 2 >= 0 );

  std::vector<float > avg_true_range (static_cast<size_t >(di_window + dx_window - 1));
  for (int ii = 0; ii < di_window + dx_window - 1; ++ii) {
    avg_true_range[ii] = eMA(true_range, ii, ii + true_range_window);
  }

  std::vector<float > dm_pos (static_cast<size_t >(dx_window + di_window - 1));
  std::vector<float > dm_neg (static_cast<size_t >(dx_window + di_window - 1));

  for (int ii = true_range_window - 1; ii < true_range_window + dx_window + di_window - 1; ++ii) {
    if ((high[ii] -  high[ii - 1] > 0) && (high[ii] -  high[ii - 1] > low[ii - 1] - low[ii]) ) {
      dm_pos[ii - true_range_window + 1] = high[ii] -  high[ii - 1] / avg_true_range[ii - true_range_window + 1];
    }
    if ( (low[ii-1] -  low[ii] > 0) && (high[ii] -  high[ii - 1] < low[ii - 1] - low[ii]) ) {
      dm_neg[ii - true_range_window + 1] = low[ii-1] - low[ii] / avg_true_range[ii - true_range_window + 1];
    }
  }

  std::vector<float > di_pos (static_cast<size_t >( dx_window ));
  std::vector<float > di_neg (static_cast<size_t >( dx_window ));
  for (int ii = 0; ii < dx_window; ++ii) {
    di_pos[ii] = eMA(dm_pos, ii, ii + di_window);
    di_neg[ii] = eMA(dm_neg, ii, ii + di_window);
  }

  std::vector<float > dx (static_cast<size_t >(dx_window));
  for (int ii = 0; ii < dx_window; ++ii) {
    dx[ii] = fabs(di_pos[ii] - di_neg[ii]) / (di_pos[ii] + di_neg[ii]) * 100;
  }

  return eMA(dx, 0, dx_window);
}


float MyLib::reverseArrangementTest(const std::vector<float> &close, int start_idx, int end_idx) {
  int sign_count = 0;
  for (int ii = start_idx; ii < end_idx - 1; ++ii) {
    for (int jj = start_idx + 1; jj < end_idx; ++jj) {
      if (close[ii] < close[jj]) {
        ++sign_count;
      } else {
        --sign_count;
      }
    }
  }

  return static_cast<float >(sign_count) /
          (static_cast<float >(end_idx-start_idx) * static_cast<float >(end_idx-start_idx - 1) / 2 );
}


MyLib::BollingerBands MyLib::bollingerBands(const std::vector<float> & close, int start_idx, int end_idx, float K) {
  float ma = sMA(close, start_idx, end_idx);
  float std_val = std(close, start_idx, end_idx);

  MyLib::BollingerBands bands (ma + K*std_val, ma, ma-K*std_val);
  return bands;
}


float MyLib::z_score(const std::vector<float> &close, int start_idx, int end_idx) {
  float ma = sMA(close, start_idx, end_idx);
  float std_val = std(close, start_idx, end_idx);
  return (close[end_idx - 1] - ma) / std_val;
}


float MyLib::bollingerRelative(const std::vector<float> &close, int start_idx, int end_idx, float K) {
  MyLib::BollingerBands bands = bollingerBands( close, start_idx, end_idx, K );
  return (close[end_idx - 1] - bands.lower) / (bands.upper - bands.lower);
}


float MyLib::RSI(const std::vector<float> &close) {
  return 0;
}


MyLib::Oscillators MyLib::oscillators(const std::vector<float> &high,
                                      const std::vector<float> &low,
                                      const std::vector<float> &close,
                                      int d_window, int min_max_window) {
  std::vector<float > ll_n (static_cast<size_t >(d_window + min_max_window - 1));
  std::vector<float > hh_n (static_cast<size_t >(d_window + min_max_window - 1));
  for (int ii = 0; ii < d_window + min_max_window - 1; ++ii) {
    ll_n[ii] = min(low, ii, ii + min_max_window);
    hh_n[ii] = min(high, ii, ii + min_max_window);
  }

  std::vector<float > fast_k (static_cast<size_t >(d_window));
  for (int ii = 0; ii < d_window; ++ii) {
    fast_k[ii] = 100 * (close[min_max_window - 1 + ii] - ll_n[ii]) / (hh_n[ii] - ll_n[ii]);
  }

  float fast_d = sMA(fast_k, 0, d_window);
  return MyLib::Oscillators(fast_k.back(), fast_d, 0);
}


float MyLib::onBalanceVolume(const std::vector<float> &close, const std::vector<float> &volume) {
  return 0;
}


float MyLib::moneyFlowIndex(const std::vector<float> &true_range, const std::vector<float> &volume) {
  return 0;
}


float
MyLib::chaikinMoneyFlow(const std::vector<float> &high, const std::vector<float> &low, const std::vector<float> &close,
                        const std::vector<float> &volume) {
  return 0;
}




