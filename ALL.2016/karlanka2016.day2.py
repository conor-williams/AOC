import itertools
import time
# takes a state and checks if any chips are burned
def violate(vio_list):
    # gen-chip pair
    pairs = map(lambda x: vio_list[1:][x:x+2], range(0,len(vio_list[1:]),2))
 
    # floors of generators
    gens = vio_list[1::2]
 
    # check if any gen-chip pair is not on same floor, if true check if any gen is on the same floor as chip
    for p in pairs:
        if p[0] != p[1]:
            if p[1] in gens:
                return True
    return False
 
 
# takes a state and checks if already visited given that all pairs are interchangeable
# [0,1,1,0,0] == [0,0,0,1,1]
def vis_state(vis_l):
    print("vis_l: ");
    print(vis_l);
    global visited_states
 
    # gen-chip pair
    pairs = map(lambda x: vis_l[1:][x:x+2], range(0,len(vis_l[1:]),2))
 
    # add floor to every pair
    state = map(lambda x: (vis_l[0], x), pairs)
 
    # create unique state by adding floor to every pair and then sort by pair
    # [0,1,1,0,0] = [0,0,0,1,1] = [(0,[0,0]),(0,[1,1])]
    sorted_by_second = sorted(state, key=lambda tup: tup[1])
 
    # check if the unique state already been visited, if not store in global visited_states
    if sorted_by_second in visited_states:
        return True
    else:
        visited_states.append(sorted_by_second)
        return False
 
 
def day11():
    t0 = time.time()
 
    # visited is queue to loop
    # ([elevator, generator1, chip1, generator2, chip2...], graph-start), where value represents floor of item
    #visited = [([0, 1, 0, 2, 0], 0)]  # test
    #visited = [([0, 0, 0, 0, 1, 0, 1, 2, 2, 2, 2], 0)]  # 1
    visited = [([0, 0, 0, 0, 1, 0, 1, 2, 2, 2, 2, 0, 0, 0, 0], 0)]  # 2
    loops = 0
    kkk = 22;
    for lk in visited:
        #print(visited)
        print(kkk);
        #if kkk == 24:
        #    return;
        kkk = kkk +1
        ##print("lk in visited...\n");
        ##print("visited : ");
        #print(visited);
        # current state
        l = lk[0]
        curr_floor = l[0]
        print("curr_floor: \n");
        print(curr_floor);
 
        # where in graph
        curr_try = lk[1]
 
        # what items are on same floor as elevator
        at_e_level = [i for i, x in enumerate(l) if x == curr_floor][1:]
 
        # possible moves based on items at_e_level, move either any combo of two or only one
        possible_moves = list(itertools.combinations(at_e_level, 2))+at_e_level
      #  print(at_e_level);

        ###print(list(itertools.combinations(at_e_level, 2)))
        ##print(at_e_level)

        ###print(possible_moves)
        
 
        # if curr floor is 0 or 3 only one direction is allowed, otherwise up and down
        if curr_floor == 0:
            dirs = [1]
        elif curr_floor == 3:
            dirs = [-1]
        else:
            dirs = [-1, 1]
 
        # copy old state that every move will be based on
        old_l = l[:]
 
        # do not go downstairs if downstairs empty
        if curr_floor == 1 and l.count(0) == 0:
            dirs = dirs[1:]
        if curr_floor == 2 and l.count(0) == 0 and l.count(1) == 0:
            dirs = dirs[1:]
 
        # do all possible moves in all possible directions
        #print("---------------\n");
        for d in dirs:
            #print("d in dirs...d: ");
            #print(d);
            #print("\n");
            for each in possible_moves:
                #print("in again...................\n");
                #print(each);
                #print(" ");
                #print(each[1]);
                loops += 1
 
                # copy old state and move from there
                test_l = old_l[:]
 
                # bring two items in elevator
                if type(each) == tuple:
                    # do not bring two items downstairs
                    if d == -1:
                        continue
                    test_l[0] = curr_floor + d
                    test_l[each[0]] = curr_floor + d
                    test_l[each[1]] = curr_floor + d
                # bring one item in elevator
                else:
                    test_l[0] = curr_floor + d
                    test_l[each] = curr_floor + d
 
 
                # if not burning chip, put in q with number in graph
                if violate(test_l) is False:
                    #print("violate false...\n");
                    # check if new state already been visited
                    #print("test_l: ");
                    #print(test_l);
                    #print("\n");
                    if vis_state(test_l) is True:
                        continue
                    else:
                        visited.append((test_l, curr_try+1))
                        #print("append...\n");
 
                # check if everything in list is on third floor, then print where in graph (moves)
                if sum(test_l) == len(test_l)*3:
                    print( 'current state:', test_l)
                    print( 'moves:', curr_try+1)
                    print( 'elapsed time:', time.time()-t0)
                    print( 'allowed states visited:', len(visited))
                    #print 'unique states visited:', len(visited_states)
                    print( 'total visits:', loops)
                    exit()
 
 
def main():
    global visited_states
    visited_states = []
    day11()
 
 
if __name__ == '__main__':
    main()
