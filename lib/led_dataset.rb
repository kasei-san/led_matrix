# encoding: utf-8
require File.join(File.dirname(__FILE__), 'bdf')

class LedDataSet
  def initialize(str)
    @binaly_arrays = str.to_bdf
    @cnt = 0
  end

  def current
    @current ||= self.next
  end

  def next
    @current = @binaly_arrays.map do |bin|
                 bin[@cnt, 16].join.to_i(2)
               end
    @cnt+=1
    @current
  end

  def reset
    @cnt = 0
    @current = nil
  end
end
