import string
import sklearn

# ***IMP*** when finding in or updating freq_count sort the tuple


# The data file. Transactions file
def read_dataFile(dataFile):
  f = open(dataFile, "r")
  transactions = []
  set_of_values = set()
  for l in f:
    temparr = []
    for e in l.strip().split(","):
      if e != '':
        temparr.append(int(e))
        set_of_values.add(int(e))
    transactions.append(temparr)

  return transactions, set_of_values


# The parameter file. MIS values of all items.
def read_paramsFile(paramFile, set_of_values):
  sdc = 0.0
  mdc = {}
  f = open(paramFile, "r")
  for l in f:
    if l.startswith("MIS"):
      e = l[l.find('(') + 1:l.find(')')]
      val = float(l[l.find("= ") + 1:])
      if (e == 'rest'):
        # loop for the rest of the unseen values
        for value in set_of_values:
          mdc[value] = val
      else:
        # insert our value
        mdc[int(e)] = val
        set_of_values.remove(int(e))
    elif l.startswith("SDC"):
      sdc = float(l[l.find("= ") + 1:])

  return sdc, mdc


# sorting MS
def sort_help(MS, all_values):
  return sorted(MS.keys(), key=lambda x: MS[x], reverse=False)


#
def init_pass(M, T, MS):
  freq = {}
  L = []
  n = len(T) + 0.0

  for tr in T:
    for elem in set(tr):  # **IMP** changed to set as we want support count
      if elem in freq:
        freq[elem] += 1
      else:
        freq[elem] = 1

  index = -1
  for i in range(len(M)):
    if (freq[M[i]] / (n + 0.0) >= MS[M[i]]):
      index = i
      break
  L.append(M[index])

  for j in range(index + 1, len(M)):
    if (freq[M[j]] / (n + 0.0) >= MS[M[index]]):
      L.append(M[j])

  return L, freq


# level2-candidate-gen function
def level2_candidate_gen(L, sdc, freq, n, MS):
  C2 = []

  for i in range(len(L)):  #changed for i and j
    l = L[i]

    if freq[l] / (n + 0.0) >= MS[l]:
      for j in range(i + 1, len(L)):
        h = L[j]

        if freq[h]/(n+0.0) >= MS[l] and \
          (abs((freq[h] / (n+0.0)) - (freq[l] / (n+0.0))) <= sdc):

          C2.append((l, h))  # tuple of l,h

  return C2


# **IMP** remove for loops?
def check_same_sets(C1, C2):
  for c1 in C1:
    if c1 not in C2:
      return False

  return True


def check_as_set(c, F):
  for f in F:
    if check_same_sets(c, f):
      return True

  return False


def check_last(C1, C2):
  c1_last = C1[-1]
  c2_last = C2[-1]

  return (c1_last not in C2) and (c2_last not in C1)


# MScandidate-gen functio
def MScandidate_gen(Fk_1, sdc, freq, n, MS):
  Ck = []

  # print("Candidate gen for:", len(Fk_1[0]) + 1)

  for f1 in Fk_1:
    for f2 in Fk_1:
      if f1[:-1] == f2[:-1] and \
         check_last(f1, f2) and \
        f1[-1] < f2[-1] and \
        (abs((freq[f1[-1]] / (n+0.0)) - (freq[f2[-1]] / (n+0.0))) <= sdc):

        c = f1[:-1]

        # **IMP**, sort here
        if MS[f2[-1]] >= MS[f1[-1]]:
          c = c + (f1[-1], f2[-1])  # adding f1 and f2's last elem
        else:
          c = c + (f2[-1], f1[-1])

        Ck.append(c)

        # print(c)

        for i in range(len(c)):
          s = c[0:i] + c[i + 1:]

          # print("   ", s)

          if c[0] in s or \
            MS[c[1]] == MS[c[0]]:
            if not check_as_set(s, Fk_1):
              Ck.remove(c)
              # print("   removed")
              break

  # print()
  return Ck


def c_in_t(c, t):
  for elem in c:
    if elem not in t:
      return False

  return True


# MSApriori Algorithm
def MSapriori(T, MS, sdc, all_values):
  M = sort_help(MS, all_values)
  L, freq = init_pass(M, T, MS)

  # print("M:", M)
  # print()
  # print("L:", L)
  # print()
  # print("freq:", freq)

  n = len(T) + 0.0  # so that we have proper double division

  F = {}

  F1 = []

  for i in L:
    if freq[i] / (n + 0.0) >= MS[i]:
      # added () because we have tuple representing sets of elems
      F1.append((i, ))

  F[1] = F1
  # print()
  # print("F with F1: ", F)

  # sort the array for each freq_coutn update or search

  # loop over freq to fill freq_count, each item in freq is now array [elem]
  # changing freq_count
  # tuple to represent the set and have a good way to keep their freq count

  freq_count = {}
  for elem in freq:
    freq_count[(elem, )] = freq[elem]

  freq_count[tuple()] = len(T)

  # print()
  # print("new freq_count =", freq_count)
  # print()

  k = 2
  prev_Ck = []
  while (len(F[k - 1]) > 0):
    Ck = []

    if k == 2:
      Ck = level2_candidate_gen(L, sdc, freq, n, MS)
    else:
      Ck = MScandidate_gen(F[k - 1], sdc, freq, n, MS)

    # print(("C" + str(k)), ":", Ck)
    # print()

    # **IMP**: assuming all candidates are sorted by MIS

    for t in T:
      for c in Ck:
        c_as_list = list(c)  # necessary as T has lists

        if c_in_t(c, t):
          if c in freq_count:
            freq_count[c] += 1
          else:
            freq_count[c] = 1

    for c in Ck:
      c_tail = c[1:]

      if c_tail not in freq_count:
        for t in T:
          if c_in_t(c_tail, t):
            if c_tail in freq_count:
              freq_count[c_tail] += 1
            else:
              freq_count[c_tail] = 1

    # end of double for
    # print(k, "freq_count: ", freq_count)

    Fk = []

    for c in Ck:
      fqc = 0.0

      if c in freq_count:
        fqc = freq_count[c] / (n + 0.0)

      # print("    ", c, "freq:", fqc, "req: ", MS[c[0]])

      if fqc >= MS[c[0]]:
        Fk.append(c)

    F[k] = Fk
    # print(("F" + str(k)), ":", Fk)
    # print("F:", F)

    prev_Ck = Ck
    k += 1
    # print()
    # end of while

  return F, freq_count


# main:

# read the data file
# t, set_of_values = read_dataFile("dataFile.txt")
t, set_of_values = read_dataFile("data-1.txt")

all_values = list(set_of_values)

# print("set_of_values size:", len(set_of_values), set_of_values)

# read the params file
# sdc, mdc = read_paramsFile("params.txt", set_of_values)
sdc, mdc = read_paramsFile("para-1-2.txt", set_of_values)

# debug print
# for tr in t:
#   print(tr)

# print()
# print("sdc:", sdc)
# print("mdc size:", len(mdc), "mdc:", mdc)

# print()
# print()

# call the ms apriori function
F, freq_count = MSapriori(t, mdc, sdc, all_values)

for k in range(1, len(F)):
  print("(Length-" + str(k), len(F[k]))

  for itemset in F[k]:
    print("    (" + \
          (" ".join(str(ele) for ele in itemset)) \
          + ") :", freq_count[itemset], ":", freq_count[itemset[1:]])

  print(")")

# **IMP** in MS cand gen, make sure not to put same elem twice, meaning, check if ik-1 not in f2 and i'k-1 not in f1

# **IMP** check for all freq access, not presenet case?

# **IMP** check for freq updates, what if already have it, dont want to increase if already present

# DOUBLE CHECK: freq updates and counting for >1 tuples,
# DOUBLE CHECK w/ prof: the final print has itemsets printed acc to MIS order
# DOUBLE CHECK: go thought the current files and check fully
