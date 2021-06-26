typedef pair<int,int> pairInt;

class Solution {
private:
    vector<vector<char>> pathGrid;
    int rowSize,colSize;
    bool isValid(int i,int j, vector<vector<int>> &visited) {
        if(i<0 or i>=rowSize or j<0 or j>=colSize)
            return false;
        if(visited[i][j]==1 or pathGrid[i][j]=='X')
            return false;
        return true;
    }
    int getFoodUtil(vector<pairInt> start) {
        queue<pairInt> bfsQue;
        for(auto entry : start) {
            bfsQue.push(entry);
        }
        cout<<start.size()<<endl;
        int distance = -1;
        vector<vector<int>> visited(rowSize);
        for(int i=0;i<rowSize;i++) {
            visited[i].resize(colSize,0);
        }
        vector<int> rowOffset{-1,0,1,0};
        vector<int> colOffset{0,1,0,-1};
        while(!bfsQue.empty()) {
            int levelSize = bfsQue.size();
            distance +=1;
            for(int j=0;j<levelSize;j++) {
                pairInt front = bfsQue.front();
                bfsQue.pop();
                visited[front.first][front.second] = 1;
                //cout<<front.first<<" "<<front.second<<endl;
                for(int i=0;i<4;i++) {
                    int nrow = front.first + rowOffset[i];
                    int ncol = front.second + colOffset[i];
                    if(isValid(nrow,ncol,visited)) {
                        if(pathGrid[nrow][ncol]=='*')
                            return distance+1;
                        bfsQue.push({nrow,ncol});
                    }
                }
                
            }
        }
        return -1;
        
    }
public:
    Solution() {
        rowSize = 0;
        colSize = 0;
    }
    int getFood(vector<vector<char>>& grid) {
        //Input Validation
        if(grid.size()==0 or grid[0].size()==0) {
            cout<<"Input with no size"<<endl;
            return -1;
        }
        bool foundStartCell=false,foundFoodCell=false;
        vector<pairInt> start;
        rowSize = grid.size();
        colSize = grid[0].size();
        for(int i=0;i<rowSize;i++) {
                for(int j=0;j<colSize;j++) {
                    if(grid[i][j]=='*') {
                        if(foundStartCell) {
                            cout<<"Input with more than one start cell"<<endl;
                            return -1;
                        }
                        foundStartCell = true;
                    }
                    else if(grid[i][j]=='#') {
                        start.push_back({i,j});
                        foundFoodCell = true;
                    }
                    else if(grid[i][j]!='O' and grid[i][j]!='X') {
                        return -1;
                    }
                }
            }
        if(!foundStartCell or !foundFoodCell)
            return -1;
        
        pathGrid = grid;
        
        int distanceToFood = -1;
        try{
            
            distanceToFood = getFoodUtil(start);
        }
        catch (exception &e) {
            cout<<"Failed with exception "<<e.what()<<endl;
            return -1;
        } 
        return distanceToFood;
    }
};
