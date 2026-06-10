"""
y, 2020.10.28
scipy.stats - normal distribution.py
https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.norm.html
"""


import scipy.stats as ss

mu, sigma = 2, 2
rv = ss.norm(loc=mu, scale=sigma)

print(f"rv.stats()={rv.stats()}")
print(f"rv.cdf({mu})={rv.cdf(mu)}")
print(f"rv.pdf({mu})={rv.pdf(mu)}")
print(f"rv.median()={rv.median()}")

print(f"ss.norm.pdf({mu}, loc={mu}, scale={sigma})={ss.norm.pdf(mu, loc=mu, scale=sigma)}")
