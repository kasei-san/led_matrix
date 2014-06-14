# encoding: utf-8
require File.join(File.dirname(__FILE__), '..', 'ext', 'LedController')
require File.join(File.dirname(__FILE__), 'led_dataset')
require 'thread'
require 'singleton'

class LedIntermediator
  include Singleton

  def initialize
    @mutex = Mutex.new
    @led_controller = LedController.new
    @led_dataset = LedDataSet.new('')
    @queue = Queue.new
    t = Thread.new do
      loop do
        begin
          @mutex.synchronize do
            @led_controller.matrix = @led_dataset.next
            if @led_dataset.finish?
              @led_dataset.reset
            end
          end

          if @led_dataset.finish?
            @obj.finish
          end
        rescue => e
          p e.message
        end
        sleep(0.01)
      end
    end
  end

  # obj has #finish
  #
  def set_finish_event(obj)
    @obj = obj
  end

  def set_str(str)
    @mutex.synchronize do
      @led_dataset = LedDataSet.new(str)
    end
  end
end
