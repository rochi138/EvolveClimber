#include <algorithm>

#include "Creature.h"

using namespace std;

namespace EC
{
    class Creature {
        Creature modified(int id) {
            Creature modifiedCreature(id, 
            vector<Node>(), vector<Muscle>(), 0, true, creatureTimer+r()*16*mutability, min(mutability*rFloat(0.8, 1.25), 2));
            for (int i = 0; i < n.size(); i++) {
            // modifiedCreature.n.add(n.get(i).modifyNode(mutability,n.size()));
            }
            for (int i = 0; i < m.size(); i++) {
            // modifiedCreature.m.add(m.get(i).modifyMuscle(n.size(), mutability));
            }
            if (rFloat(0, 1) < bigMutationChance*mutability || n.size() <= 2) { //Add a node
            modifiedCreature.addRandomNode();
            }
            if (rFloat(0, 1) < bigMutationChance*mutability) { //Add a muscle
            modifiedCreature.addRandomMuscle(-1, -1);
            }
            if (rFloat(0, 1) < bigMutationChance*mutability && modifiedCreature.n.size() >= 4) { //Remove a node
            modifiedCreature.removeRandomNode();
            }
            if (rFloat(0, 1) < bigMutationChance*mutability && modifiedCreature.m.size() >= 2) { //Remove a muscle
            modifiedCreature.removeRandomMuscle();
            }
            modifiedCreature.checkForOverlap();
            modifiedCreature.checkForLoneNodes();
            modifiedCreature.checkForBadAxons();
            return modifiedCreature;
        }
        void checkForOverlap() {
            vector<int> bads;
            for (int i = 0; i < m.size(); i++) {
                for (int j = i+1; j < m.size(); j++) {
                    // if (m.get(i).c1 == m.get(j).c1 && m.get(i).c2 == m.get(j).c2) {
                    // bads.add(i);
                    // }
                    // else if (m.get(i).c1 == m.get(j).c2 && m.get(i).c2 == m.get(j).c1) {
                    // bads.add(i);
                    // }
                    // else if (m.get(i).c1 == m.get(i).c2) {
                    // bads.add(i);
                    // }
                }
            }
            // for (int i = bads.size()-1; i >= 0; i--) {
            //     int b = bads.get(i)+0;
            //     if (b < m.size()) {
            //         m.remove(b);
            //     }
            // }
        }
        void checkForLoneNodes() {
            if (n.size() >= 3) {
                for (int i = 0; i < n.size(); i++) {
                    int connections = 0;
                    int connectedTo = -1;
                    for (int j = 0; j < m.size(); j++) {
                        if (m.get(j).c1 == i || m.get(j).c2 == i) {
                            connections++;
                            connectedTo = j;
                        }
                    }
                    if (connections <= 1) {
                        int newConnectionNode = floor(rFloat(0, n.size()));
                        while (newConnectionNode == i || newConnectionNode == connectedTo) {
                            newConnectionNode = floor(rFloat(0, n.size()));
                        }
                        addRandomMuscle(i, newConnectionNode);
                    }
                }
            }
        }
        void checkForBadAxons(){
            for (int i = 0; i < n.size(); i++) {
                Node ni = n.get(i);
                if(ni.axon1 >= n.size()){
                    ni.axon1 = rand() % n.size();
                }
                if(ni.axon2 >= n.size()){
                    ni.axon2 = rand() % n.size();
                }
            }
            for (int i = 0; i < m.size(); i++) {
                Muscle mi = m.get(i);
                if(mi.axon >= n.size()){
                    mi.axon = getNewMuscleAxon(n.size());
                }
            }
            
            for (int i = 0; i < n.size(); i++) {
                Node ni = n.get(i);
                ni.safeInput = (operationAxons[ni.operation] == 0);
            }
            int iterations = 0;
            bool didSomething = false;
            
            while(iterations < 1000){
                didSomething = false;
                for (int i = 0; i < n.size(); i++) {
                    Node ni = n.get(i);
                    if(!ni.safeInput){
                        if((operationAxons[ni.operation] == 1 && n.get(ni.axon1).safeInput) ||
                        (operationAxons[ni.operation] == 2 && n.get(ni.axon1).safeInput && n.get(ni.axon2).safeInput)){
                            ni.safeInput = true;
                            didSomething = true;
                        }
                    }
                }
                if(!didSomething){
                    iterations = 10000;
                }
            }
            
            for (int i = 0; i < n.size(); i++) {
                Node ni = n.get(i);
                if(!ni.safeInput){ // This node doesn't get its input from a safe place.  CLEANSE IT.
                    ni.operation = 0;
                    ni.value = rFloat(0,1);
                }
            }
        }
        void addRandomNode() {
            int parentNode = floor(rFloat(0, n.size()));
            float ang1 = rFloat(0, 2*PI);
            float distance = sqrt(rFloat(0, 1));
            float x = n.get(parentNode).x+cos(ang1)*0.5*distance;
            float y = n.get(parentNode).y+sin(ang1)*0.5*distance;
            
            int newNodeCount = n.size()+1;
            
            n.add(new Node(x, y, 0, 0, 0.4, rFloat(0, 1), rFloat(0,1), floor(rFloat(0,operationCount)),
            floor(rFloat(0,newNodeCount)),floor(rFloat(0,newNodeCount)))); //random(0.1,1),random(0,1)
            int nextClosestNode = 0;
            float record = 100000;
            for (int i = 0; i < n.size()-1; i++) {
            if (i != parentNode) {
                float dx = n.get(i).x-x;
                float dy = n.get(i).y-y;
                if (sqrt(dx*dx+dy*dy) < record) {
                record = sqrt(dx*dx+dy*dy);
                nextClosestNode = i;
                }
            }
            }
            addRandomMuscle(parentNode, n.size()-1);
            addRandomMuscle(nextClosestNode, n.size()-1);
        }
        void addRandomMuscle(int tc1, int tc2) {
            int axon = getNewMuscleAxon(n.size());
            if (tc1 == -1) {
                tc1 = rand() % n.size();
                tc2 = tc1;
                while (tc2 == tc1 && n.size () >= 2) {
                    tc2 = rand() % n.size();
                }
            }
            float len = random(0.5, 1.5);
            if (tc1 != -1) {
                len = dist(n.get(tc1).x, n.get(tc1).y, n.get(tc2).x, n.get(tc2).y);
            }
            m.add(new Muscle(axon, tc1, tc2, len, rFloat(0.02, 0.08)));
        }
        void removeRandomNode() {
            int choice = rand() % n.size();
            // n.remove(choice);
            int i = 0;
            // while (i < m.size ()) {
            //     if (m.get(i).c1 == choice || m.get(i).c2 == choice) {
            //         m.remove(i);
            //     }
            //     else {
            //         i++;
            //     }
            // }
            for (int j = 0; j < m.size(); j++) {
                // if (m.get(j).c1 >= choice) {
                //     m.get(j).c1--;
                // }
                // if (m.get(j).c2 >= choice) {
                //     m.get(j).c2--;
                // }
            }
        }
        void removeRandomMuscle() {
            int choice = floor(rFloat(0, m.size()));
            // m.remove(choice);
        }
        Creature copyCreature(int newID) {
            vector<Node> n2;
            vector<Muscle> m2;
            for (int i = 0; i < n.size(); i++) {
                // n2.add(this.n.get(i).copyNode());
            }
            for (int i = 0; i < m.size(); i++) {
                // m2.add(this.m.get(i).copyMuscle());
            }
            if (newID == -1) {
                newID = id;
            }
            return new Creature(newID, n2, m2, d, alive, creatureTimer, mutability);
        }
    };
}
