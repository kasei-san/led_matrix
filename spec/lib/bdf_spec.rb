# encoding: utf-8
require "bdf"

describe Bdf do
  subject{ described_class.instance }

  let(:binaly_arrays){
    [
      '000000000001000010001000',
      '000000000000100010001000',
      '000000000000111111111111',
      '000000000000000010001000',
      '000000000100000000000000',
      '001111000010001111111110',
      '010000100010001000100010',
      '000000100000001000100010',
      '001111100000101111111110',
      '010000100000100000100000',
      '100000100001001111111100',
      '100000100001000000100000',
      '100001100010011111111111',
      '011110100010000001010000',
      '000000000100000110001100',
      '000000000100011000000011',
    ]
  }

  it 'Bdf is singleton class' do
    Bdf.instance.object_id.should eq Bdf.instance.object_id
  end

  describe '.string_to_bdf' do
    it 'change string to binaly arrays' do
      subject.string_to_bdf('a漢').map{|line| line.join}.should eq binaly_arrays
    end

    it 'String.to_bdf too' do
      'a漢'.to_bdf.map{|line| line.join}.should eq binaly_arrays
    end
  end
end
