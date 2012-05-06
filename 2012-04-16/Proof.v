Require Import Arith.
Require Import Arith.Euclid.
Require Import Arith.Wf_nat.
Require Import List.
Require Import Omega.

Inductive gcd_trace : nat -> nat -> Set :=
      gcdt_bottom : forall (a : nat), gcd_trace a 0
    | gcdt : forall (a b c q : nat),
          a >= b -> b > c -> a = q * b + c ->
          gcd_trace b c -> gcd_trace a b.

Lemma make_gcdt_left : forall (a b : nat), a >= b -> gcd_trace a b.
  induction a as [a IH] using lt_wf_rec.
  intros.
  destruct b.
  apply (gcdt_bottom a).
  case (le_lt_eq_dec (S b) a) ; auto ; intro.
  generalize (eucl_dev (S b) (le_n_S 0 b (le_0_n b)) a) ; intro.
  destruct H0.
  apply (gcdt a (S b) r q) ; auto.
  apply IH ; auto ; omega.
  apply (gcdt a (S b) 0 1) ; auto ; try omega.
  apply (gcdt_bottom (S b)).
Defined.

Lemma make_gcdt : forall (a b : nat), sum (gcd_trace a b) (gcd_trace b a).
  intros.
  case (le_ge_dec a b) ; intro.
  right ; apply (make_gcdt_left b a l).
  left ; apply (make_gcdt_left a b g).
Defined.

Fixpoint gcdt_to_list (a b : nat) (t : gcd_trace a b) : list (nat * nat) :=
  match t with
    | gcdt_bottom a => (a, b) :: nil
    | gcdt _ b c _ _ _ _ t' => (a, b) :: gcdt_to_list b c t'
  end.

Lemma gcdt_uniqueness : forall (a b : nat) (t1 t2 : gcd_trace a b),
    gcdt_to_list a b t1 = gcdt_to_list a b t2.
  intros.
  inversion t1.
  


Fixpoint gcd (a b : nat) (t : gcd_trace a b) : nat :=
  match t with
    | gcdt_bottom a => a
    | gcdt _ b c _ _ _ _ t' => gcd b c t'
  end.

Fixpoint gcd_complexity (a b : nat) (t : gcd_trace a b) : nat :=
  match t with
    | gcdt_bottom a => 1
    | gcdt _ b c _ _ _ _ t' => S (gcd_complexity b c t')
  end.

