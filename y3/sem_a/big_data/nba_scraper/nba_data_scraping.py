'''
Created on Jan 22, 2018

@author: yali
'''
import os

from calendar import monthrange
from nba_py import game, Scoreboard
import pandas as p
import argparse


MONTHS_BEFORE_NEWYEAR = range(10,13)
MONTHS_AFTER_NEWYEAR = range(1,5)
UNNEEDED_FEATURES = ['GAME_ID','TEAM_ID', 'TEAM_ABBREVIATION', 'TEAM_CITY', 'MIN', 'FGA', 'FGM', 'FG_PCT', 'PLUS_MINUS']
NO_DEFICIT_FEATURES = ['PCT', 'TEAM', 'ID', 'MIN', 'OUTCOME', 'PTS', 'PLUS_MINUS']
AWAY_WIN = [0,1]
HOME_WIN = [1,0]
CSV = '.csv'



class Create_csv_files(object):
    '''
    classdocs
    '''


    def __init__(self, root_dir, season):
        '''
        @param root_dir: a path to the root directory which all the files will be stored
        @type root_dir: string
        @param season: the years the season is being played
        @type season: list of strings, containing 2 strings
        '''
        self._root_dir = root_dir +'/'
        # Season must be a list with two strings in the form of [2012,2013]
        if not (len(season) == 2 and (season[1] - season[0] == 1)):
            print('season in not correct')
        self._season = season
        self.df = p.DataFrame()
        self._current_teams = []
        
    def _create_directory(self, curr_dir):
        if not os.path.exists(curr_dir):
            os.makedirs(curr_dir)

    def season_name(self):
        return str(self._season[0]) + '-' + str(self._season[1])
    
    def scrape_season(self, test=False):
        
        season_dir = self._root_dir + '/' + self.season_name() + '/'
        month_years = [(self._season[0], month) for month in MONTHS_BEFORE_NEWYEAR] + \
                      [(self._season[1], month) for month in MONTHS_AFTER_NEWYEAR]

        self._create_directory(season_dir)

        if test:
            self.scrape_month(season_dir, 2014, 11, first_day=22,last_day=25)
        else:
            # Scrape the first part of the season
            for year, month in month_years:
                print('currently scraping: {}/{}'.format(year,month))
                self.scrape_month(season_dir, year, month)
            
        all_boxscores_file = season_dir + 'all.csv'
        print("create a csv file with all the games named ", all_boxscores_file)
        self.df.to_csv(all_boxscores_file)
    
    def scrape_month(self, root_dir, year, month, first_day=1, last_day=31):
        '''
        Create a directory containing all the boxscore of the entered month
        '''
        last_day = min([monthrange(year, month)[1], last_day])
        curr_dir = root_dir + str(month) + '/'
        
        self._create_directory(curr_dir)
        
        for day in range(first_day, last_day+1):
            print("currently scraping {day}/{month}/{year}".format(day=day, month=month, year=year))
            self.process_scoreboard(year, month, day, curr_dir)
                       
    def _fill_teams(self, sb):
        es = sb.east_conf_standings_by_day()
        ws = sb.west_conf_standings_by_day()

        self._current_teams += list(ws['TEAM']) + list(es['TEAM'])

    def process_scoreboard(self, year, month, day, root_dir):
        '''
        Create csv files with game id inside a directory by day
        
        '''
        sb = Scoreboard(month=month, day=day, year=year)
        curr_dir = root_dir + str(day) + '/'

        if not self._current_teams:
            self._fill_teams(sb)
        self._create_directory(curr_dir)
            
        for gid in sb.available().GAME_ID:
            self.boxscore_to_csv(gid, curr_dir)
            
    def remove_columns(self, ts):
        for feature in UNNEEDED_FEATURES:
            del ts[feature]
        return ts
        
    def add_deficit_column(self, ts, feature):
        ts['DEFICIT_'+feature] = ts[feature] / sum(ts[feature])
        return ts
    
    def add_columns(self, ts):
        '''
        Adding columns to a given dataframe
        @param ts: box score
        @type ts: dataframe 
        '''
        # Adding 2 pt field goals data
        ts['FG2M'] = ts['FGM'] - ts['FG3M']
        ts['FG2A'] = ts['FGA'] - ts['FG3A']
        ts['FG2_PCT'] = ts['FG2M'] / ts['FG2A']

        # 1 represents win 0 represents loss

        ts['OUTCOME'] = HOME_WIN if ts['PLUS_MINUS'][0] > 0 else AWAY_WIN

        # Add deficit 
        for c in ts.columns:
            if any(s in c for s in NO_DEFICIT_FEATURES):
                continue
            ts = self.add_deficit_column(ts, c)
        
        return ts

    def irrelevant_data(self, ts):
        if len(ts.index) == 0:
            return True

        if len(ts.dropna()) < 2:
            return True

        if not all(team in self._current_teams for team in ts['TEAM_CITY']):
            return True

        return False


    # TODO: add manipulation over the data
    def manipulate_df(self, ts):
        '''
        Currently does nothing. Opening up in case of making some manuipulations
        on the teams box score
        '''
        if self.irrelevant_data(ts):
            return None
        
        ts = self.add_columns(ts)
        
        ts = self.remove_columns(ts)
                
        return ts
    
    def boxscore_to_csv(self, gid, root_dir, append=False):
        '''
        Create a csv file from a boxscore according to the game id
        '''

        bs = game.Boxscore(gid)
        team_stats = bs.team_stats()
        team_stats = self.manipulate_df(team_stats)
        if team_stats is None :
            return
        
        csv_name = root_dir + gid + CSV
        
        if append:
            # TODO: add case for appending the data frame information to an existing csv file
            pass
        else:
            team_stats.to_csv(csv_name)
            
        self.df = self.df.append(team_stats, ignore_index=True)


def test():
    # Testing variables
    print("Testing Create csv files object")
    gid = '0041400122'
    season = [2014, 2015]
    year = season[1]
    month = 2
    start = 13
    day = 21


    #parser = argparse.ArgumentParser(description="")
    #parser.add_argument('--directory', dest='dir')
    #parser.add_argument('--season', dest='se', nargs='+', type=int)
    #args = parser.parse_args()

    myDir = '/Users/noamstolero/Documents/CS/yali_noam/y3/sem_a/big_data/nba_scraper'
    se = [2013, 2014]

    my_tool = Create_csv_files(myDir, se)
    #temp_dir = args.dir + '/'
    
    my_tool.scrape_season(test=True)     # Test scraping a whole season
    #my_tool.scrape_month(root_dir=temp_dir, year=2015, month=3, first_day=1)
    #my_tool.boxscore_to_csv(gid, '/Users/noamstolero/Documents/CS/yali_noam/y3/sem_a/big_data/nba_scraper/2014-2015/')


def main():
    parser = argparse.ArgumentParser(description="")
    parser.add_argument('--directory', dest='dir')
    parser.add_argument('--season', dest='se', nargs='+', type=int)
    args = parser.parse_args()

    my_tool = Create_csv_files(args.dir, args.se)
    my_tool.scrape_season()


if __name__ == "__main__":
    main()