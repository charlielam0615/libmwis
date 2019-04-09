import numpy as np
import mwis

# an example corresponds to "MHT revisited" paper, Fig.2

conn = np.array([[False, False, False, False, False, False, False, False],
                 [False, False, True,  True,  False, False, False, False],
                 [False, True,  False, True,  True,  True,  False, False],
                 [False, True,  True,  False, True,  True,  False, False],
                 [False, False, True,  True,  False, True,  True,  True],
                 [False, False, True,  True,  True,  False, True,  True],
                 [False, False, False, False, True,  True,  False, True],
                 [False, False, False, False, True,  True,  True,  False]], dtype=np.bool)
weights = np.array([[5], [210], [223], [221], [123], [121], [132], [134]], dtype=np.uint32)
results = mwis.mwis(conn, weights)
print(results)
