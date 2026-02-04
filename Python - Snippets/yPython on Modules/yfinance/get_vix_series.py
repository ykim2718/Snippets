import yfinance as yf
from datetime import datetime, timedelta
import pandas as pd
from typing import Optional

# Yahoo Finance 티커 정의
yahoo_tickers = {
    '^VIX': 'VIX (변동성 지수)',
    '^GSPC': 'S&P 500',
    '^DJI': '다우존스 산업평균지수',
    '^IXIC': '나스닥 종합지수',
    '^KS11': '코스피',
    '^KQ11': '코스닥',
    '^N225': '니케이 225'
}


def get_yahoo_series(ticker: str, days: int = 7) -> Optional[pd.Series]:
    """
    주어진 기간의 Yahoo Finance 데이터를 pandas Series로 반환

    Parameters:
        ticker (str): Yahoo Finance ticker (예: '^VIX', '^GSPC' 등)
        days (int): 조회할 기간 (일 단위, 기본값 7일)

    Returns:
        Optional[pd.Series]: 일별 종가 데이터. 오류 발생시 None 반환
    """
    # 티커가 유효한지 확인
    if ticker not in yahoo_tickers:
        print(f"Error: '{ticker}' is not a valid ticker")
        print("Available tickers:")
        for t, desc in yahoo_tickers.items():
            print(f"  {t}: {desc}")
        return None

    # 날짜 범위 설정
    end_date = datetime.now()
    start_date = end_date - timedelta(days=days)

    try:
        # 데이터 가져오기
        data = yf.download(ticker, start=start_date, end=end_date)

        # 종가(Close) 데이터만 Series로 추출
        price_series = data['Close']

        # Series 이름 설정
        price_series.name = yahoo_tickers[ticker]

        return price_series

    except Exception as e:
        print(f"데이터 조회 중 오류 발생: {e}")
        return None


if __name__ == "__main__":
    # VIX 데이터 조회
    vix_data = get_yahoo_series('^VIX')
    # S&P 500 데이터 조회
    # sp500_data = get_yahoo_series('^GSPC')
    # 30일치 나스닥 데이터 조회
    # nasdaq_data = get_yahoo_series('^IXIC', days=30)

    if vix_data is not None:
        print(f"\n=== 최근 일주일 {vix_data.name} 데이터 ===")
        print(vix_data)
        print("\n기초 통계량:")
        print(f"평균: {vix_data.mean():.2f}")
        print(f"최대값: {vix_data.max():.2f}")
        print(f"최소값: {vix_data.min():.2f}")

    # 다른 지수 데이터 조회 예시
    sp500_data = get_yahoo_series('^GSPC')
    if sp500_data is not None:
        print(f"\n=== 최근 일주일 {sp500_data.name} 데이터 ===")
        print(sp500_data)
