#include <stdio.h>
#include <limits.h>

#define countof(X) (sizeof(X)/sizeof(X[0]))

int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a < b ? b : a;
}

// globals
int boss_damage, best, hard;

struct state {
  int mana, player_hp, boss_hp, mana_spent;
  char shield_turns, poison_turns, recharge_turns;
};

void every_turn(struct state* s) {
  if (s->shield_turns > 0) {
    s->shield_turns -= 1;
  }
  if (s->poison_turns > 0) {
    s->boss_hp -= 3;
    s->poison_turns -= 1;
  }
  if (s->recharge_turns > 0) {
    s->mana += 101;
    s->recharge_turns -= 1;
  }
}

// forward declaration
void player_turn(struct state s);

void boss_turn(struct state s) {
  every_turn(&s);
  int player_armor = s.shield_turns > 0 ? 7 : 0;
  s.player_hp -= max(boss_damage - player_armor, 1);
  if (s.player_hp > 0) {
    player_turn(s);
  }
}

void magic_missile(struct state s) {
  s.boss_hp -= 4;
  if (s.boss_hp <= 0) {
    best = min(best, s.mana_spent);
  } else {
    boss_turn(s);
  }
}

void drain(struct state s) {
  s.boss_hp -= 2;
  s.player_hp += 2;
  if (s.boss_hp <= 0) {
    best = min(best, s.mana_spent);
  } else {
    boss_turn(s);
  }
}

void shield(struct state s) {
  if (s.shield_turns == 0) {
    s.shield_turns = 6;
    boss_turn(s);
  }
}

void poison(struct state s) {
  if (s.poison_turns == 0) {
    s.poison_turns = 6;
    boss_turn(s);
  }
}

void recharge(struct state s) {
  if (s.recharge_turns == 0) {
    s.recharge_turns = 5;
    boss_turn(s);
  }
}

struct {
  int cost;
  void (*f)(struct state);
} spells[] = {
  { 53, magic_missile },
  { 73, drain },
  { 113, shield },
  { 173, poison },
  { 229, recharge },
};

void player_turn(struct state s) {
  int i;

  if (hard) {
    s.player_hp -= 1;
    if (s.player_hp <= 0) {
      return;
    }
  }
  every_turn(&s);
  if (s.boss_hp <= 0) {
    best = min(best, s.mana_spent);
    return;
  }
  for (i = 0; i < countof(spells); i += 1) {
    int cost = spells[i].cost;
    if (s.mana >= cost && s.mana_spent + cost < best) {
      s.mana -= cost;
      s.mana_spent += cost;
      spells[i].f(s);
      s.mana_spent -= cost;
      s.mana += cost;
    } else {
      return;
    }
  }
}

int main(int argc, char* argv[]) {
  int boss_initial_hp;

  scanf("Hit Points: %d\n", &boss_initial_hp);
  scanf("Damage: %d\n", &boss_damage);

  struct state initial = {
    500, 50, boss_initial_hp,
    0, 0, 0, 0
  };
  best = INT_MAX;
  player_turn(initial);
  printf("first half: %d\n", best);

  best = INT_MAX;
  hard = 1;
  player_turn(initial);
  printf("second half: %d\n", best);

  return 0;
}
