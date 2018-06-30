/**
  Handout #1: Deduplicate in Dafny.
  Francisco Cunha, #45412
 */

/**
  Checks whether or not array a's first n elements are sorted.
  @param a {int[]} - the array to check.
  @param n {int}   - range of elements to check (i.e. first n).
  @return {bool}
  @note a predicate is simply a function that returns a boolean.
 */
predicate sorted(a: array<int>, n: int)
  reads a
  requires 0 <= n <= a.Length
{
  forall i, j :: 0 <= i < j < n ==> a[i] <= a[j]
}

/**
  Checks whether or not array a's first n elements are unique.
  @param a {int[]} - the array to check.
  @param n {int}   - range of elements to check (i.e. first n).
  @return {bool}
  @note a predicate is simply a function that returns a boolean.
 */
predicate unique(a: array<int>, n: int)
  reads a
  requires 0 <= n <= a.Length
{
  forall i, j :: 0 <= i < j < n ==> a[i] != a[j]
}

/**
  Checks whether or not array b contains value v in somewhere in the 0..m index interval.
  @param b {int[]} - the array to check.
  @param m {int}   - range of elements to check (i.e. first m).
  @param v {int}   - value to check for.
  @return {bool}
  @note a predicate is simply a function that returns a boolean.
 */
predicate contains(b: array<int>, m: int, v: int)
  reads b
  requires 0 <= m <= b.Length 
{
  v in b[..m]
}

/**
  Removes duplicates from array a (an array with n elements). The result is a new array (b),
  (an unique, duplicate-free version of array a), and m, the number of elements in b.
  @param a {int[]}  - the array we want to remove duplicates from.
  @param n {int}    - number of elements in array a.
  @return b {int[]} - an unique, duplicate-free version of array a. 
  @return m {int}   - number of elements in array b.
 */
method Deduplicate(a: array<int>, n: int) returns (b: array<int>, m: int)
  requires 0 <= n <= a.Length
  requires sorted(a, n)
  ensures 0 <= m <= b.Length
  ensures b.Length <= a.Length
  ensures sorted(b, m) && unique(b, m)
  ensures fresh(b) && a == old(a)
  // ensures forall i :: 0 <= i < n ==> contains(b, m, a[i]) -> After many, many tries, could not prove this.
{
  b := new int[n];

  if n == 0 { return b, 0; }

  var i := 1;
  b[0] := a[0];
  m := 1;

  while i < n
    decreases n - i
    invariant 1 <= i <= n
    invariant 1 <= m <= i
    invariant sorted(b, m) && unique(b, m)
    // invariant forall x :: 0 <= x < i ==> contains(b, m, a[x]) -> After many, many tries, could not prove this.
  {
    if a[i] > b[m - 1] {
      m := m + 1;
      b[m - 1] := a[i];
      assert contains(b, m, a[i]);
    }
    i := i + 1;
  }
}
